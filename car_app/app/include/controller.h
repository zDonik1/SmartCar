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

#include <tensorflow/lite/interpreter.h>
#include <tensorflow/lite/kernels/register.h>
#include <tensorflow/lite/model.h>
#include <tensorflow/lite/tools/gen_op_registration.h>

#include <iussensor.h>
#include <iirsensor.h>
#include <imovement.h>
#include <iavoider.h>
#include <iusobstacledetector.h>
#include <icamera.h>

#include <dooncemanager.h>


class Controller : public QObject
{
    Q_OBJECT

public:
    Controller(std::shared_ptr<IUSSensor> usSensor,
               std::shared_ptr<IMovement> movement,
               std::shared_ptr<IUSObstacleDetector> frontObstacleDetector,
               std::shared_ptr<ICamera> camera,
               int tickInterval,
               bool isDebug = false,
               QObject *parent = nullptr);

    virtual ~Controller() override;

    bool makeTreeFromFile(const std::string &filename);
    bool makeTreeFromText(const std::string &text);

    bool makeModelFromFile(const std::string &filename);

    void start();
    void stop();

    template<typename InputType>
    void addTreeConstant(const std::string &key, const InputType &constant)
    {
        m_blackboard->set(key, constant);
    }

private slots:
    void tickTree();

private:
    void registerNodes();
    void startSensors();
    void stopSensors();
    void requestSensorsUpdate();
    void preprocessFrame(FramePtr frame);

private:
    BT::Blackboard::Ptr m_blackboard;
    BT::BehaviorTreeFactory m_factory;
    BT::Tree m_tree;
    std::unique_ptr<BT::StdCoutLogger> m_logger;

    std::unique_ptr<tflite::FlatBufferModel> m_model;
    tflite::ops::builtin::BuiltinOpResolver m_resolver;
    std::unique_ptr<tflite::Interpreter> m_interpreter;

    std::shared_ptr<IUSSensor> m_usSensor;
    std::vector<std::shared_ptr<ISensor>> m_sensors;

    std::shared_ptr<ICamera> m_camera;
    FramePtr m_frame;

    std::shared_ptr<IMovement> m_movement;
    std::shared_ptr<IUSObstacleDetector> m_frontObstacleDetector;

    QTimer m_tickTimer;
    DoOnceManager m_doOnceManager;
    int m_tickInterval = 1; // ms
    bool m_isDebug = false;
    bool m_behaviorTreeInitialized = false;
};
