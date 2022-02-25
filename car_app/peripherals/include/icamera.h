/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 24/02/2022
 *
 *************************************************************************/

#include <functional>
#include <memory>

#include "iframe.h"

class ICamera
{
public:
    virtual FramePtr newFrame() const = 0;
};
