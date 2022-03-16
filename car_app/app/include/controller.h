/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/


#pragma once

#include <memory>

#include <QObject>
#include <QTimer>

#include <behaviortree_cpp_v3/bt_factory.h>
#include <behaviortree_cpp_v3/loggers/bt_cout_logger.h>

#include <icontroller.h>
#include <iussensor.h>
#include <iirsensor.h>
#include <imovement.h>
#include <iirvectorservice.h>
#include <iusobstacledetector.h>


class Controller : public QObject, public IController
{
    Q_OBJECT

public:
    Controller(std::shared_ptr<IUSSensor> usSensor,
               std::shared_ptr<IIRSensor> leftTracerSensor,
               std::shared_ptr<IIRSensor> rightTracerSensor,
               std::shared_ptr<IIRSensor> leftDetectorSensor,
               std::shared_ptr<IIRSensor> rightDetectorSensor,
               std::shared_ptr<IMovement> movement,
               std::shared_ptr<IIRVectorService> tracer,
               std::shared_ptr<IIRVectorService> sideObstacleDetector,
               std::shared_ptr<IUSObstacleDetector> frontObstacleDetector,
               QObject *parent = nullptr);

    virtual ~Controller() override;

    virtual bool makeTreeFromFile(const std::string &filename) override;
    virtual bool makeTreeFromText(const std::string &text) override;

    virtual void start() override;
    virtual void stop() override;

private slots:
    void tickTree();

private:
    BT::Blackboard::Ptr createAndInitBlackboard();
    void registerNodes();
    void startSensors();
    void stopSensors();
    void requestSensorsUpdate();

private:
    BT::BehaviorTreeFactory m_factory;
    BT::Tree m_tree;
    std::unique_ptr<BT::StdCoutLogger> m_logger;

    std::shared_ptr<IUSSensor> m_usSensor;
    std::shared_ptr<IIRSensor> m_leftTracerSensor;
    std::shared_ptr<IIRSensor> m_rightTracerSensor;
    std::shared_ptr<IIRSensor> m_leftDetectorSensor;
    std::shared_ptr<IIRSensor> m_rightDetectorSensor;

    std::vector<std::shared_ptr<ISensor>> m_sensors;

    std::shared_ptr<IMovement> m_movement;
    std::shared_ptr<IIRVectorService> m_tracer;
    std::shared_ptr<IIRVectorService> m_sideObstacleDetector;
    std::shared_ptr<IUSObstacleDetector> m_frontObstacleDetector;

    QTimer m_tickTimer;
    int m_obstacleCount = 0;
    bool m_hasFinishedObstacleTwo = false;
};
