/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/05/2022
 *
 *************************************************************************/

#pragma once

#include <icamera.h>
#include <iimageprocessor.h>
#include <rmovecontroller.h>

class Controller : public QObject
{
public:
    Controller(std::shared_ptr<ICamera> camera,
               std::shared_ptr<IImageProcessor> imageProcessor,
               std::shared_ptr<IMovement> movement,
               QObject *parent = nullptr);
    virtual ~Controller() override;

    void start();
    void stop();

private:
    std::shared_ptr<ICamera> m_camera;
    std::shared_ptr<IImageProcessor> m_imageProcessor;
    RMoveController m_moveController;
};
