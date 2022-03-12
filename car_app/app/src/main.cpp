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
#include <doublelinetracer.h>
#include <irobstacledetector.h>

using namespace std;

constexpr auto MOTOR_LEFT_FORWARD_PIN = 1;
constexpr auto MOTOR_LEFT_BACKWARD_PIN = 4;
constexpr auto MOTOR_RIGHT_FORWARD_PIN = 5;
constexpr auto MOTOR_RIGHT_BACKWARD_PIN = 6;

constexpr auto US_TRIGGER_PIN = 28;
constexpr auto US_ECHO_PIN = 29;

constexpr auto IR_OBSTACLE_LEFT_PIN = 27;
constexpr auto IR_OBSTACLE_RIGHT_PIN = 26;

constexpr auto IR_TRACER_LEFT_PIN = 10;
constexpr auto IR_TRACER_RIGHT_PIN = 11;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    auto movement = make_unique<Movement>(make_unique<MotorActuator>(MOTOR_LEFT_FORWARD_PIN,
                                                                     MOTOR_LEFT_BACKWARD_PIN),
                                          make_unique<MotorActuator>(MOTOR_RIGHT_FORWARD_PIN,
                                                                     MOTOR_RIGHT_BACKWARD_PIN));

    auto leftTracer = make_shared<IRSensor>(IR_TRACER_LEFT_PIN);
    auto rightTracer = make_shared<IRSensor>(IR_TRACER_RIGHT_PIN);

    auto leftDetector = make_shared<IRSensor>(IR_OBSTACLE_LEFT_PIN);
    auto rightDetector = make_shared<IRSensor>(IR_OBSTACLE_RIGHT_PIN);

    Controller controller(make_shared<USSensor>(US_TRIGGER_PIN, US_ECHO_PIN),
                          leftTracer,
                          rightTracer,
                          leftDetector,
                          rightDetector,
                          move(movement),
                          make_unique<DoubleLineTracer>(leftTracer, rightTracer),
                          make_unique<IRObstacleDetector>(leftDetector, rightDetector));
    controller.makeTreeFromFile("");

    return a.exec();
}
