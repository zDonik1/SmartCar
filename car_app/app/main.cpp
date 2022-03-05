/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QTimer>
#include <QDebug>

#include <usobstacledetector.h>
#include <ussensor.h>

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

    //    USObstacleDetector detector(make_unique<USSensor>(US_TRIGGER_PIN, US_ECHO_PIN));
    //    detector.addThreshold(15);
    //    detector.addThreshold(30);
    //    detector.addThreshold(45);

    //    QObject::connect(&detector, &USObstacleDetector::thresholdCrossed, &a, [&](int index, bool less) {
    //        qDebug() << index << detector.thresholds().at(index) << less;
    //    });

    //    detector.start();

    USSensor sensor(US_TRIGGER_PIN, US_ECHO_PIN);
    sensor.start();

    return a.exec();
}
