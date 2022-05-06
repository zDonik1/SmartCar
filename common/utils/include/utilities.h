/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 06/05/2022
 *
 *************************************************************************/

#pragma once

constexpr auto NS_IN_SEC = 1e9;
constexpr auto MS_IN_SEC = 1e3;

auto framerateFromMs(long long unsigned int period)
{
    return MS_IN_SEC / period;
}

auto framerateFromNs(long long unsigned int period)
{
    return NS_IN_SEC / period;
}
