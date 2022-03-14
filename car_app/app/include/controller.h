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

#include <icontroller.h>
#include <iussensor.h>
#include <iirsensor.h>
#include <imovement.h>
#include <ilinetracer.h>
#include <iirobstacledetector.h>
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
               std::unique_ptr<IMovement> movement,
               std::unique_ptr<ILineTracer> tracer,
               std::unique_ptr<IIRObstacleDetector> sideObstacleDetector,
               std::unique_ptr<IUSObstacleDetector> frontObstacleDetector,
               QObject *parent = nullptr);

    virtual ~Controller() override = default;

    virtual bool makeTreeFromFile(const std::string &filename) override;
    virtual bool makeTreeFromText(const std::string &text) override;

    virtual void start() override;
    virtual void stop() override;

private slots:
    void tickTree();

private:
    void registerNodes();
    void requestSensorsUpdate();

private:
    BT::BehaviorTreeFactory m_factory;
    BT::Tree m_tree;

    std::shared_ptr<IUSSensor> m_usSensor;
    std::shared_ptr<IIRSensor> m_leftTracerSensor;
    std::shared_ptr<IIRSensor> m_rightTracerSensor;
    std::shared_ptr<IIRSensor> m_leftDetectorSensor;
    std::shared_ptr<IIRSensor> m_rightDetectorSensor;

    std::unique_ptr<IMovement> m_movement;
    std::unique_ptr<ILineTracer> m_tracer;
    std::unique_ptr<IIRObstacleDetector> m_sideObstacleDetector;
    std::unique_ptr<IUSObstacleDetector> m_frontObstacleDetector;

    QTimer m_tickTimer;
    int m_obstacleCount = 0;
    bool m_hasFinishedObstacleTwo = false;
};
