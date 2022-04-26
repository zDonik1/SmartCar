/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 15/04/2022
 *
 *************************************************************************/

#pragma once

#include <opencv2/core/mat.hpp>

struct Frame
{
    Frame(unsigned int seq, cv::Mat img) : sequence(seq), image(img) {}

public:
    cv::Mat image;
    unsigned int sequence;
    float framerate;
};

using FramePtr = std::shared_ptr<Frame>;
