/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#include <controller.h>

#include <QDebug>

#include <opencv2/imgproc.hpp>

#include <move.h>
#include <avoid.h>
#include <noobstacleinfront.h>
#include <avoidernotblocked.h>
#include <doonce.h>
#include <common.h>

using namespace std;
using namespace BT;
using namespace tflite;
using namespace cv;

constexpr auto SENSOR_UPDATE_INTERVAL = 0; // ms, 0 means manual ticking

Controller::Controller(std::shared_ptr<IUSSensor> usSensor,
                       std::shared_ptr<IMovement> movement,
                       std::shared_ptr<IUSObstacleDetector> frontObstacleDetector,
                       std::shared_ptr<ICamera> camera,
                       int tickInterval,
                       bool isDebug,
                       QObject *parent)
    : QObject(parent), m_blackboard(Blackboard::create()), m_usSensor(usSensor),
      m_movement(movement), m_frontObstacleDetector(frontObstacleDetector), m_camera(camera),
      m_receiver(CONTROL_PORT), m_tickInterval(tickInterval), m_isDebug(isDebug)
{
    registerNodes();

    connect(m_camera.get(), &ICamera::frameReady, this, [this](FramePtr frame) { m_frame = frame; });

    connect(&m_receiver, &ICommandReceiver::connected, this, [this] {
        m_imageSender = make_unique<ImageSender>(m_receiver.host(), FRAME_PORT);

        connect(m_camera.get(), &ICamera::frameReady, m_imageSender.get(), &IImageSender::sendFrame);

        m_imageSender->start();
    });

    connect(&m_receiver, &ICommandReceiver::disconnected, this, &Controller::stopImageSender);

    connect(&m_tickTimer, &QTimer::timeout, this, &Controller::tickTree);

    m_sensors.push_back(m_usSensor);
}

Controller::~Controller()
{
    Controller::stop();
}

bool Controller::makeTreeFromFile(const std::string &filename)
{
    try {
        m_tree = m_factory.createTreeFromFile(filename, m_blackboard);
        m_behaviorTreeInitialized = true;
        if (m_isDebug) {
            m_logger = make_unique<StdCoutLogger>(m_tree);
        }
    } catch (const std::runtime_error &e) {
        qDebug() << e.what();
        return false;
    }
    return true;
}

bool Controller::makeTreeFromText(const std::string &text)
{
    try {
        m_tree = m_factory.createTreeFromText(text, m_blackboard);
        m_behaviorTreeInitialized = true;
        if (m_isDebug) {
            m_logger = make_unique<StdCoutLogger>(m_tree);
        }
    } catch (const std::runtime_error &e) {
        qDebug() << e.what();
        return false;
    }
    return true;
}

bool Controller::makeModelFromFile(const std::string &filename)
{
    m_model = FlatBufferModel::BuildFromFile(filename.c_str());
    if (!m_model)
        return false;

    if (InterpreterBuilder(*m_model, m_resolver)(&m_interpreter) != kTfLiteOk)
        return false;

    if (m_interpreter->AllocateTensors() != kTfLiteOk)
        return false;

    return true;
}

void Controller::start()
{
    if (!m_behaviorTreeInitialized) {
        qWarning() << "The behavior tree has not been initalized";
        return;
    }

    m_camera->start();
    m_tickTimer.start(m_tickInterval);
    startSensors();
    requestSensorsUpdate();
}

void Controller::stop()
{
    m_camera->stop();
    m_imageSender->stop();
    m_tickTimer.stop();
    stopSensors();
}

void Controller::tickTree()
{
    requestSensorsUpdate();
    m_tree.tickRoot();
}

void Controller::stopImageSender()
{
    if (!m_imageSender)
        return;

    m_imageSender->stop();
    m_imageSender.release();
}

void Controller::registerNodes()
{
    // ---- action nodes

    auto moveBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<Move>(m_movement, name, config);
    };

    auto stopBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<Stop>(m_movement, name);
    };

    m_factory.registerBuilder<Move>("Move", moveBuilder);
    m_factory.registerBuilder<Stop>("Stop", stopBuilder);

    m_factory.registerSimpleAction("FollowLane", [this](TreeNode &) {
        if (!m_frame)
            return NodeStatus::FAILURE;

        preprocessFrame(m_frame);
        auto tensor = m_interpreter->input_tensor(0);
        auto &mat = m_frame->image;
        int count = 0; // count of current elements in relation to data in input tensor
        for (int i = 0; i < mat.rows; ++i) {
            for (int j = 0; j < mat.cols; ++j) {
                for (int k = 0; k < mat.channels(); ++k) {
                    tensor->data.f[count++] = static_cast<float>(mat.at<uchar>(i, j, k)) / 255;
                }
            }
        }

        if (m_interpreter->Invoke() != kTfLiteOk) {
            qWarning() << "Couldn't run prediction";
            return NodeStatus::FAILURE;
        }

        auto output = *m_interpreter->typed_output_tensor<float>(0);

        qDebug() << output;
        //        qDebug() << vector.x << vector.y;
        Vector vector;
        auto delta = 35;
        if (output < 90 - delta) {
            vector = {1.f, 0.8f};
        } else if (output > 90 + delta) {
            vector = {-1.f, 0.8f};
        } else {
            vector = {static_cast<float>(cos(output * M_PI / 180)),
                      static_cast<float>(sin(output * M_PI / 180))};
            vector *= 0.5;
        }
        qDebug() << vector.x << vector.y;
        m_movement->move(vector);
        return NodeStatus::SUCCESS;
    });


    // ---- condition nodes

    auto noObstacleInFrontBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<NoObstacleInFront>(m_usSensor, name, config);
    };

    m_factory.registerBuilder<NoObstacleInFront>("NoObstacleInFront", noObstacleInFrontBuilder);


    // ---- decorator nodes

    auto doOnceBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<DoOnce>(m_doOnceManager, name, config);
    };

    auto resetDoOnceBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<ResetDoOnce>(m_doOnceManager, name, config);
    };

    m_factory.registerBuilder<DoOnce>("DoOnce", doOnceBuilder);
    m_factory.registerBuilder<ResetDoOnce>("ResetDoOnce", resetDoOnceBuilder);
}

void Controller::startSensors()
{
    for (const auto &sensor : m_sensors) {
        sensor->start(SENSOR_UPDATE_INTERVAL);
    }
}

void Controller::stopSensors()
{
    for (const auto &sensor : m_sensors) {
        sensor->stop();
    }
}

void Controller::requestSensorsUpdate()
{
    for (const auto &sensor : m_sensors) {
        sensor->requestReading();
    }
}

void Controller::preprocessFrame(FramePtr frame)
{
    Rect cropRect(0, frame->image.rows / 2, frame->image.cols, frame->image.rows / 2);
    frame->image = frame->image(cropRect);
    cvtColor(frame->image, frame->image, COLOR_BGR2YUV);
    GaussianBlur(frame->image, frame->image, {3, 3}, 0);
    resize(frame->image, frame->image, {200, 66});
}
