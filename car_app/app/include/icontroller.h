/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#pragma once

#include <string>


class IController
{
public:
    virtual bool makeTreeFromFile(const std::string &filename) = 0;
    virtual bool makeTreeFromText(const std::string &text) = 0;

    /** starts ticking the behavior tree */
    virtual void start() = 0;
    virtual void stop() = 0;
};
