/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#include <controller.h>

#include <QDebug>

#include <move.h>
#include <avoid.h>
#include <noobstacleinfront.h>
#include <avoidernotblocked.h>
#include <doonce.h>

using namespace std;
using namespace BT;

constexpr auto DEBUG = true;
constexpr auto TICK_INTERVAL = DEBUG ? 1000 : 1; // ms
constexpr auto SENSOR_UPDATE_INTERVAL = 0; // ms, 0 means manual ticking

Controller::Controller(std::shared_ptr<IUSSensor> usSensor,
                       std::shared_ptr<IIRSensor> leftTracerSensor,
                       std::shared_ptr<IIRSensor> rightTracerSensor,
                       std::shared_ptr<IIRSensor> leftDetectorSensor,
                       std::shared_ptr<IIRSensor> rightDetectorSensor,
                       std::shared_ptr<IMovement> movement,
                       std::shared_ptr<IAvoider> tracer,
                       std::shared_ptr<IAvoider> sideObstacleDetector,
                       std::shared_ptr<IUSObstacleDetector> frontObstacleDetector,
                       int tickInterval,
                       bool isDebug,
                       QObject *parent)
    : QObject(parent), m_blackboard(Blackboard::create()), m_usSensor(usSensor),
      m_leftTracerSensor(leftTracerSensor), m_rightTracerSensor(rightTracerSensor),
      m_leftDetectorSensor(leftDetectorSensor), m_rightDetectorSensor(rightDetectorSensor),
      m_movement(movement), m_tracer(tracer), m_sideObstacleDetector(sideObstacleDetector),
      m_frontObstacleDetector(frontObstacleDetector), m_tickInterval(tickInterval)
{
    registerNodes();

    connect(&m_tickTimer, &QTimer::timeout, this, &Controller::tickTree);

    m_sensors.push_back(m_usSensor);
    m_sensors.push_back(m_leftTracerSensor);
    m_sensors.push_back(m_rightTracerSensor);
    m_sensors.push_back(m_leftDetectorSensor);
    m_sensors.push_back(m_rightDetectorSensor);

    if (isDebug) {
        m_logger = make_unique<StdCoutLogger>(m_tree);
    }
}

Controller::~Controller()
{
    Controller::stop();
}

bool Controller::makeTreeFromFile(const std::string &filename)
{
    try {
        m_tree = m_factory.createTreeFromFile(filename, m_blackboard);
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
    } catch (const std::runtime_error &e) {
        qDebug() << e.what();
        return false;
    }
    return true;
}

void Controller::start()
{
    m_tickTimer.start(m_tickInterval);
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
    requestSensorsUpdate();
    m_tree.tickRoot();
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

    auto avoidObstacleBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<Avoid>(m_movement, m_sideObstacleDetector, name, config);
    };

    auto avoidLineBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<Avoid>(m_movement, m_tracer, name, config);
    };

    m_factory.registerBuilder<Move>("Move", moveBuilder);
    m_factory.registerBuilder<Stop>("Stop", stopBuilder);
    m_factory.registerBuilder<Avoid>("AvoidObstacle", avoidObstacleBuilder);
    m_factory.registerBuilder<Avoid>("AvoidLine", avoidLineBuilder);


    // ---- condition nodes

    auto noObstacleInFrontBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<NoObstacleInFront>(m_usSensor, name, config);
    };

    auto sidesNotBlockedBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<AvoiderNotBlocked>(m_sideObstacleDetector, name, config);
    };

    auto tracersNotBlockedBuilder = [this](const string &name, const NodeConfiguration &config) {
        return make_unique<AvoiderNotBlocked>(m_tracer, name, config);
    };

    m_factory.registerBuilder<NoObstacleInFront>("NoObstacleInFront", noObstacleInFrontBuilder);
    m_factory.registerBuilder<AvoiderNotBlocked>("SidesNotBlocked", sidesNotBlockedBuilder);
    m_factory.registerBuilder<AvoiderNotBlocked>("TracersNotBlocked", tracersNotBlockedBuilder);


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
