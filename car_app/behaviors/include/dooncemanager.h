/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 20/03/2022
 *
 *************************************************************************/

#pragma once

#include <unordered_map>

class DoOnce;

class DoOnceManager
{
public:
    void addDoOnceNode(const std::string &id, DoOnce &node);
    void removeNode(const std::string &id);
    bool resetNode(const std::string &id);

private:
    std::unordered_map<std::string, DoOnce &> m_doOnceMap;
};
