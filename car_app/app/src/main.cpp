/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include <controller.h>
#include <ussensor.h>
#include <irsensor.h>
#include <motoractuator.h>
#include <movement.h>
#include <debugmovement.h>
#include <doublelinetracer.h>
#include <obstacleavoider.h>
#include <usobstacledetector.h>

using namespace std;

constexpr auto DEBUG = true;
constexpr auto TREE_TICK_INTERVAL = DEBUG ? 1000 : 1; // ms

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

constexpr auto XML_TREE_FILE = "test_do_once.xml";


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto leftMotors = make_shared<MotorActuator>(MOTOR_LEFT_FORWARD_PIN, MOTOR_LEFT_BACKWARD_PIN);
    auto rightMotors = make_shared<MotorActuator>(MOTOR_RIGHT_FORWARD_PIN, MOTOR_RIGHT_BACKWARD_PIN);

    //    auto movement = make_unique<Movement>(move(leftMotors), move(rightMotors));
    auto movement = make_shared<DebugMovement>();

    auto usSensor = make_shared<USSensor>(US_TRIGGER_PIN, US_ECHO_PIN);

    auto leftTracer = make_shared<IRSensor>(IR_TRACER_LEFT_PIN);
    auto rightTracer = make_shared<IRSensor>(IR_TRACER_RIGHT_PIN);

    auto leftDetector = make_shared<IRSensor>(IR_OBSTACLE_LEFT_PIN);
    auto rightDetector = make_shared<IRSensor>(IR_OBSTACLE_RIGHT_PIN);

    Controller controller(usSensor,
                          leftTracer,
                          rightTracer,
                          leftDetector,
                          rightDetector,
                          move(movement),
                          make_shared<DoubleLineTracer>(leftTracer, rightTracer),
                          make_shared<ObstacleAvoider>(leftDetector, rightDetector),
                          make_shared<USObstacleDetector>(usSensor),
                          TREE_TICK_INTERVAL,
                          DEBUG);

    controller.makeTreeFromFile(string{BEHAVIORS_PATH} + XML_TREE_FILE);
    controller.start();

    return a.exec();
}
