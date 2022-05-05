/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#include <controller.h>

using namespace std;

Controller::Controller(shared_ptr<ICamera> camera,
                       shared_ptr<IImageProcessor> imageProcessor,
                       shared_ptr<IMovement> movement,
                       QObject *parent)
    : QObject(parent), m_camera(camera), m_imageProcessor(imageProcessor),
      m_moveController(movement)
{
    connect(m_camera.get(),
            &ICamera::frameReady,
            m_imageProcessor.get(),
            &IImageProcessor::processFrame);
}

Controller::~Controller()
{
    stop();
}

void Controller::start()
{
    m_camera->start();
    m_imageProcessor->start();
    m_moveController.start();
}

void Controller::stop()
{
    m_camera->stop();
    m_imageProcessor->stop();
    m_moveController.stop();
}
