/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 20/03/2022
 *
 *************************************************************************/

#include <dooncemanager.h>

#include <doonce.h>

using namespace std;

void DoOnceManager::addDoOnceNode(const string &id, DoOnce &node)
{
    m_doOnceMap.insert({id, node});
}

void DoOnceManager::removeNode(const string &id)
{
    m_doOnceMap.erase(id);
}

bool DoOnceManager::resetNode(const string &id)
{
    auto itr = m_doOnceMap.find(id);
    if (itr == end(m_doOnceMap))
        return false;

    itr->second.reset();
    return true;
}
