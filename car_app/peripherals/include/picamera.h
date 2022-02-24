/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#pragma once

#include <icamera.h>

namespace cv {
class VideoCapture;
}

class PICamera : public ICamera
{
public:
    PICamera();
    virtual ~PICamera();

    virtual FramePtr newFrame() const override;

private:
    std::unique_ptr<cv::VideoCapture> m_capture;
};
