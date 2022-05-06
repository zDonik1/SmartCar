/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#include <controller.h>

#include <QDir>
#include <QDateTime>

#include <opencv2/imgcodecs.hpp>

#include <common.h>

using namespace std;
using namespace cv;

constexpr auto TRAIN_DATA_DIR = "training_data";

Controller::Controller(shared_ptr<ICamera> camera, shared_ptr<IMovement> movement, QObject *parent)
    : QObject(parent), m_camera(camera), m_moveController(movement, MOVE_PORT)
{
    QDir().mkdir(TRAIN_DATA_DIR);
    connect(m_camera.get(), &ICamera::frameReady, this, [this](FramePtr frame) {
        // ignoring no movement and when moving backwards
        if (m_moveController.vector().isZero() || m_moveController.vector().y < 0)
            return;

        auto filename = QString("%1/%2 %3:%4.jpg")
                            .arg(TRAIN_DATA_DIR,
                                 QDateTime::currentDateTime().toString("dd-MM-yyyy_hh:mm:ss.zzz"))
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
