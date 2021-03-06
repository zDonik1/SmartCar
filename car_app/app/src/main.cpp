/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QDebug>

#include <ussensor.h>
#include <motoractuator.h>
#include <movement.h>
#include <debugmovement.h>
#include <usobstacledetector.h>
#include <lccamera.h>
#include <controller.h>
#include <common.h>

using namespace std;

constexpr auto DEBUG = false;
constexpr auto TREE_TICK_INTERVAL = DEBUG ? 1000 : 25; // ms
constexpr auto XML_TREE_FILE = "test_follow_lane.xml";
constexpr auto LANE_FOLLOW_MODEL_FILE = "lane_navigation.tflite";

constexpr auto MOTOR_LEFT_FORWARD_PIN = 1;
constexpr auto MOTOR_LEFT_BACKWARD_PIN = 4;
constexpr auto MOTOR_RIGHT_FORWARD_PIN = 5;
constexpr auto MOTOR_RIGHT_BACKWARD_PIN = 6;

constexpr auto US_TRIGGER_PIN = 28;
constexpr auto US_ECHO_PIN = 29;

constexpr auto IR_OBSTACLE_LEFT_PIN = 27;
constexpr auto IR_OBSTACLE_RIGHT_PIN = 26;

constexpr auto IR_TRACER_LEFT_PIN = 11;
constexpr auto IR_TRACER_RIGHT_PIN = 10;

constexpr auto DEFAULT_CAMERA = 0;
constexpr unsigned int CAPTURE_HEIGHT = 150;
constexpr unsigned int CAPTURE_WIDTH = CAPTURE_HEIGHT * ASPECT_RATIO;

int main(int argc, char *argv[])
{
    qRegisterMetaType<FramePtr>("FramePtr");

    QCoreApplication a(argc, argv);

    auto leftMotors = make_unique<MotorActuator>(MOTOR_LEFT_FORWARD_PIN, MOTOR_LEFT_BACKWARD_PIN);
    auto rightMotors = make_unique<MotorActuator>(MOTOR_RIGHT_FORWARD_PIN, MOTOR_RIGHT_BACKWARD_PIN);

    shared_ptr<IMovement> movement;
    if (DEBUG)
        movement = make_shared<DebugMovement>();
    else
        movement = make_shared<Movement>(move(leftMotors), move(rightMotors));

    auto usSensor = make_shared<USSensor>(US_TRIGGER_PIN, US_ECHO_PIN);

    auto obstacleDetector = make_shared<USObstacleDetector>(usSensor);

    auto camera = make_shared<LCCamera>(DEFAULT_CAMERA, CAPTURE_HEIGHT, CAPTURE_WIDTH);

    Controller controller(usSensor, movement, obstacleDetector, camera, TREE_TICK_INTERVAL, DEBUG);
    if (controller.makeTreeFromFile(string{BEHAVIORS_PATH} + XML_TREE_FILE)
        && controller.makeModelFromFile(string{MODELS_PATH} + LANE_FOLLOW_MODEL_FILE)) {
        controller.start();
    } else {
        qWarning() << "Couldn't start controller";
    }

    return a.exec();
}
