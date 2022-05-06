/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#include <controller.h>

#include <QDir>

#include "opencv2/imgcodecs.hpp"

using namespace std;
using namespace cv;

constexpr auto TRAIN_DATA_DIR = "training_data1";

Controller::Controller(shared_ptr<ICamera> camera, shared_ptr<IMovement> movement, QObject *parent)
    : QObject(parent), m_camera(camera), m_moveController(movement)
{
    QDir().mkdir(TRAIN_DATA_DIR);
    connect(m_camera.get(), &ICamera::frameReady, this, [this](FramePtr frame) {
        auto filename = QString("%1/%2-%3:%4.jpg")
                            .arg(TRAIN_DATA_DIR)
                            .arg(frame->sequence)
                            .arg(m_moveController.vector().x)
                            .arg(m_moveController.vector().y);
        imwrite(filename.toStdString(), frame->image);
    });
}

Controller::~Controller()
{
    stop();
}

void Controller::start()
{
    m_camera->start();
    m_moveController.start();
}

void Controller::stop()
{
    m_camera->stop();
    m_moveController.stop();
}
