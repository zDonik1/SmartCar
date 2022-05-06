/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <QCoreApplication>
#include <QDebug>

#include <motoractuator.h>
#include <movement.h>
#include <debugmovement.h>
#include <lccamera.h>
#include <controller.h>
#include <common.h>

using namespace std;

constexpr auto MOTOR_LEFT_FORWARD_PIN = 1;
constexpr auto MOTOR_LEFT_BACKWARD_PIN = 4;
constexpr auto MOTOR_RIGHT_FORWARD_PIN = 5;
constexpr auto MOTOR_RIGHT_BACKWARD_PIN = 6;

constexpr auto DEFAULT_CAMERA = 0;
constexpr unsigned int CAPTURE_HEIGHT = 480;
constexpr unsigned int CAPTURE_WIDTH = CAPTURE_HEIGHT * ASPECT_RATIO;

int main(int argc, char *argv[])
{
    qRegisterMetaType<FramePtr>("FramePtr");

    QCoreApplication a(argc, argv);

//    auto movement = make_shared<Movement>(make_unique<MotorActuator>(MOTOR_LEFT_FORWARD_PIN,
//                                                                     MOTOR_LEFT_BACKWARD_PIN),
//                                          make_unique<MotorActuator>(MOTOR_RIGHT_FORWARD_PIN,
//                                                                     MOTOR_RIGHT_BACKWARD_PIN));
    auto movement = make_shared<DebugMovement>();

    Controller controller(make_shared<LCCamera>(DEFAULT_CAMERA, CAPTURE_HEIGHT, CAPTURE_WIDTH),
                          movement);

    controller.start();

    return a.exec();
}
