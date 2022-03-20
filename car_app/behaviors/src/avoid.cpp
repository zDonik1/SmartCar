/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 17/03/2022
 *
 *************************************************************************/

#include <avoid.h>

using namespace std;
using namespace BT;

Avoid::Avoid(shared_ptr<IMovement> movement,
             shared_ptr<IAvoider> avoider,
             const string &name,
             const NodeConfiguration &config)
    : StatefulActionNode(name, config), m_movement(movement), m_avoider(avoider)
{}

NodeStatus Avoid::onStart()
{
    if (m_avoider->isBlocked()) {
        m_movement->move(m_avoider->vector());
        return NodeStatus::RUNNING;
    } else {
        return NodeStatus::FAILURE;
    }
}

NodeStatus Avoid::onRunning()
{
    if (m_avoider->isBlocked()) {
        m_movement->move(m_avoider->vector());
        return NodeStatus::RUNNING;
    } else {
        m_movement->stop();
        return NodeStatus::SUCCESS;
    }
}

void Avoid::onHalted()
{
    m_movement->stop();
}
