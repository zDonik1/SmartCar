/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#include <controller.h>

#include <QDebug>

using namespace std;
using namespace BT;

constexpr auto DEBUG = false;
constexpr auto TICK_INTERVAL = DEBUG ? 250 : 20; // ms
constexpr auto SENSOR_UPDATE_INTERVAL = 0; // ms, 0 means manual ticking
constexpr auto US_OBSTACLE_THRESHOLD = 15; // cm
constexpr auto OBSTACLE_TO_DODGE = 2;


Controller::Controller(std::shared_ptr<IUSSensor> usSensor,
                       std::shared_ptr<IIRSensor> leftTracerSensor,
                       std::shared_ptr<IIRSensor> rightTracerSensor,
                       std::shared_ptr<IIRSensor> leftDetectorSensor,
                       std::shared_ptr<IIRSensor> rightDetectorSensor,
                       std::shared_ptr<IMovement> movement,
                       std::shared_ptr<IAvoider> tracer,
                       std::shared_ptr<IAvoider> sideObstacleDetector,
                       std::shared_ptr<IUSObstacleDetector> frontObstacleDetector,
                       QObject *parent)
    : QObject(parent), m_usSensor(usSensor), m_leftTracerSensor(leftTracerSensor),
      m_rightTracerSensor(rightTracerSensor), m_leftDetectorSensor(leftDetectorSensor),
      m_rightDetectorSensor(rightDetectorSensor), m_movement(movement),
      m_tracer(tracer), m_sideObstacleDetector(sideObstacleDetector),
      m_frontObstacleDetector(frontObstacleDetector)
{
    registerNodes();

    connect(&m_tickTimer, &QTimer::timeout, this, &Controller::tickTree);

    m_sensors.push_back(m_usSensor);
    m_sensors.push_back(m_leftTracerSensor);
    m_sensors.push_back(m_rightTracerSensor);
    m_sensors.push_back(m_leftDetectorSensor);
    m_sensors.push_back(m_rightDetectorSensor);
}

Controller::~Controller()
{
    Controller::stop();
}

bool Controller::makeTreeFromFile(const std::string &filename)
{
    try {
        m_tree = m_factory.createTreeFromFile(filename, createAndInitBlackboard());
    } catch (const std::runtime_error &e) {
        qDebug() << e.what();
        return false;
    }
    return true;
}

bool Controller::makeTreeFromText(const std::string &text)
{
    try {
        m_tree = m_factory.createTreeFromText(text, createAndInitBlackboard());
    } catch (const std::runtime_error &e) {
        qDebug() << e.what();
        return false;
    }
    return true;
}

void Controller::start()
{
    if (DEBUG) {
        m_logger = make_unique<StdCoutLogger>(m_tree);
    }

    m_tickTimer.start(TICK_INTERVAL);
    startSensors();
    requestSensorsUpdate();
}

void Controller::stop()
{
    m_tickTimer.stop();
    stopSensors();
}

void Controller::tickTree()
{
    if (DEBUG) {
        qDebug() << "Ticking tree";
    }

    requestSensorsUpdate();
    m_tree.tickRoot();
}

Blackboard::Ptr Controller::createAndInitBlackboard()
{
    auto blackboard = Blackboard::create();
    return blackboard;
}

void Controller::registerNodes()
{
    // ---- condition nodes

    m_factory.registerSimpleCondition("IsObstacleInFront", [this](TreeNode &) {
        if (m_usSensor->distance() < 0)
            return NodeStatus::FAILURE;

        return m_usSensor->distance() < US_OBSTACLE_THRESHOLD ? NodeStatus::SUCCESS
                                                              : NodeStatus::FAILURE;
    });

    m_factory.registerSimpleCondition("IsObstacleOnSide", [this](TreeNode &) {
        return m_leftDetectorSensor->isBlocked() || m_rightDetectorSensor->isBlocked()
                   ? NodeStatus::SUCCESS
                   : NodeStatus::FAILURE;
    });

    m_factory.registerSimpleCondition("IsOnLine", [this](TreeNode &) {
        return m_leftTracerSensor->isBlocked() || m_rightTracerSensor->isBlocked()
                   ? NodeStatus::SUCCESS
                   : NodeStatus::FAILURE;
    });
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
