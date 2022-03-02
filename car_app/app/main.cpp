/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QThread>
#include <QDebug>

#include <ussensor.h>

constexpr auto MOTOR_LEFT_FORWARD_PIN = 1;
constexpr auto MOTOR_LEFT_BACKWARD_PIN = 4;
constexpr auto MOTOR_RIGHT_FORWARD_PIN = 5;
constexpr auto MOTOR_RIGHT_BACKWARD_PIN = 6;

constexpr auto US_TRIGGER_PIN = 28;
constexpr auto US_ECHO_PIN = 29;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    USSensor usSensor(US_TRIGGER_PIN, US_ECHO_PIN);
    usSensor.start();
    usSensor.setThreshold(30);

    QObject::connect(&usSensor, &USSensor::thresholdCrossed, &a, [&usSensor](bool less) {
        qDebug() << (less ? "less" : "more") << usSensor.distance();
    });

    return a.exec();
}
