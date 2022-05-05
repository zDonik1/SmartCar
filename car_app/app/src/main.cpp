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
#include <imageprocessor.h>
#include <rmovecontroller.h>
#include <common.h>

using namespace std;

constexpr auto DEBUG = true;
constexpr auto TREE_TICK_INTERVAL = DEBUG ? 1000 : 1; // ms
constexpr auto XML_TREE_FILE = "test_do_once.xml";

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

constexpr auto IP = "192.168.100.180";
constexpr auto DEFAULT_CAMERA = 0;
constexpr unsigned int CAPTURE_HEIGHT = 480;
constexpr unsigned int CAPTURE_WIDTH = CAPTURE_HEIGHT * ASPECT_RATIO;

int main(int argc, char *argv[])
{
    qRegisterMetaType<FramePtr>("FramePtr");

    QCoreApplication a(argc, argv);

    QHostAddress host{IP};

    auto leftMotors = make_unique<MotorActuator>(MOTOR_LEFT_FORWARD_PIN, MOTOR_LEFT_BACKWARD_PIN);
    auto rightMotors = make_unique<MotorActuator>(MOTOR_RIGHT_FORWARD_PIN, MOTOR_RIGHT_BACKWARD_PIN);

    auto movement = make_unique<Movement>(move(leftMotors), move(rightMotors));
//        auto movement = make_unique<DebugMovement>();

    auto usSensor = make_shared<USSensor>(US_TRIGGER_PIN, US_ECHO_PIN);


    auto camera = make_shared<LCCamera>(DEFAULT_CAMERA, CAPTURE_HEIGHT, CAPTURE_WIDTH);
    ImageProcessor processor;

    RMoveController moveController(host, move(movement));

    camera->start();
    processor.start(camera);
    moveController.start();

    return a.exec();
}
