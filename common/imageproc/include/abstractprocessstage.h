/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 06/05/2022
 *
 *************************************************************************/

#pragma once

#include <frame.h>

class AbstractProcessStage
{
public:
    virtual void process(FramePtr frame) = 0;
};
