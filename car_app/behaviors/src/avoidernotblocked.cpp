/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 20/03/2022
 *
 *************************************************************************/

#include <avoidernotblocked.h>

using namespace std;
using namespace BT;

AvoiderNotBlocked::AvoiderNotBlocked(shared_ptr<IAvoider> avoider,
                                     const string &name,
                                     const NodeConfiguration &config)
    : ConditionNode(name, config)
{}

NodeStatus AvoiderNotBlocked::tick()
{
    return m_avoider->isBlocked() ? NodeStatus::FAILURE : NodeStatus::SUCCESS;
}
