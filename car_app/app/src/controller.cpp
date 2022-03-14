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
constexpr auto US_OBSTACLE_THRESHOLD = 15; // cm
constexpr auto OBSTACLE_TO_DODGE = 2;

// registering custom Vector type in BehaviorTree
namespace BT {
template<>
inline Vector convertFromString(StringView str)
{
    auto parts = splitString(str, ',');
    if (parts.size() != 2) {
        throw RuntimeError("invalid input in behavior tree");
    } else {
        Vector vector;
        vector.x = convertFromString<float>(parts[0]);
        vector.y = convertFromString<float>(parts[1]);
        return vector;
    }
}
} // namespace BT


Controller::Controller(std::shared_ptr<IUSSensor> usSensor,
                       std::shared_ptr<IIRSensor> leftTracerSensor,
                       std::shared_ptr<IIRSensor> rightTracerSensor,
                       std::shared_ptr<IIRSensor> leftDetectorSensor,
                       std::shared_ptr<IIRSensor> rightDetectorSensor,
                       std::shared_ptr<IMovement> movement,
                       std::shared_ptr<ILineTracer> tracer,
                       std::shared_ptr<IIRObstacleDetector> sideObstacleDetector,
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
    requestSensorsUpdate();
}

void Controller::stop()
{
    m_tickTimer.stop();
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
    // --- ports list

    PortsList obstacleNumberPort = {InputPort<int>("obstacle_number")};
    PortsList vectorPort = {InputPort<Vector>("vector")};


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

    m_factory.registerSimpleCondition(
        "WhichObstacle",
        [this](TreeNode &self) {
            auto obstacleNumber = self.getInput<int>("obstacle_number");
            if (!obstacleNumber) {
                qDebug() << "Couldn't find port: obstacle_number";
                return NodeStatus::FAILURE;
            }

            return obstacleNumber.value() == m_obstacleCount ? NodeStatus::SUCCESS
                                                             : NodeStatus::FAILURE;
        },
        obstacleNumberPort);

    m_factory.registerSimpleCondition(
        "HasFinishedObstacle",
        [this](TreeNode &self) {
            auto obstacleNumber = self.getInput<int>("obstacle_number");
            if (!obstacleNumber) {
                qDebug() << "Couldn't find port: obstacle_number";
                return NodeStatus::FAILURE;
            }

            if (obstacleNumber.value() == OBSTACLE_TO_DODGE) {
                return m_hasFinishedObstacleTwo ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
            } else {
                qDebug() << "Obstacle numbers other than" << OBSTACLE_TO_DODGE
                         << "are not supported";
                return NodeStatus::FAILURE;
            }
        },
        obstacleNumberPort);

    // ---- action nodes

    m_factory.registerSimpleAction(
        "Move",
        [this](TreeNode &self) {
            auto vector = self.getInput<Vector>("vector");
            if (!vector) {
                qDebug() << "Couldn't find port: vector";
                return NodeStatus::FAILURE;
            }

            m_movement->move(vector.value());
            return NodeStatus::SUCCESS;
        },
        vectorPort);

    m_factory.registerSimpleAction("Stop", [this](TreeNode &) {
        m_movement->stop();
        return NodeStatus::SUCCESS;
    });

    m_factory.registerSimpleAction("AvoidLine", [this](TreeNode &) {
        m_movement->move(m_tracer->vector());
        return NodeStatus::SUCCESS;
    });

    m_factory.registerSimpleAction("AvoidSideObstacle", [this](TreeNode &) {
        m_movement->move(m_sideObstacleDetector->vector());
        return NodeStatus::SUCCESS;
    });

    m_factory.registerSimpleAction(
        "SetFinishedObstacle",
        [this](TreeNode &self) {
            auto obstacleNumber = self.getInput<int>("obstacle_number");
            if (!obstacleNumber) {
                qDebug() << "Couldn't find port: obstacle_number";
                return NodeStatus::FAILURE;
            }

            if (obstacleNumber.value() == OBSTACLE_TO_DODGE) {
                m_hasFinishedObstacleTwo = true;
                return NodeStatus::SUCCESS;
            } else {
                qDebug() << "Obstacle numbers other than" << OBSTACLE_TO_DODGE
                         << "are not supported";
                return NodeStatus::FAILURE;
            }
        },
        obstacleNumberPort);

    m_factory.registerSimpleAction("IncrementObstacleCount", [this](TreeNode &) {
        ++m_obstacleCount;
        qDebug() << "incremented obstacle count to" << m_obstacleCount;
        return NodeStatus::SUCCESS;
    });
}

void Controller::requestSensorsUpdate()
{
    m_usSensor->requestDistance();
    m_leftTracerSensor->requestCheckBlocked();
    m_rightTracerSensor->requestCheckBlocked();
}
