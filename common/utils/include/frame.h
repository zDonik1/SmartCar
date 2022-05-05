/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 15/04/2022
 *
 *************************************************************************/

#pragma once

#include <opencv2/core/mat.hpp>

#include <common.h>

struct Frame
{
    Frame() = default;
    Frame(unsigned int seq, cv::Mat img) : sequence(seq), image(img) {}

public:
    cv::Mat image;
    SequenceType sequence = 0;
    float framerate = 0;
};

using FramePtr = std::shared_ptr<Frame>;
