/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 17/03/2022
 *
 *************************************************************************/

#pragma once

#include <vector.h>

#include <behaviortree_cpp_v3/basic_types.h>


namespace BT {

template<>
inline Vector convertFromString(StringView str)
{
    auto parts = splitString(str, ',');
    if (parts.size() != 2) {
        throw RuntimeError("invalid input in behavior tree");
    } else {
        Vector vector;
        vector.x = convertFromString<float>(parts[0]);
        vector.y = convertFromString<float>(parts[1]);
        return vector;
    }
}

} // namespace BT
