/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 20/03/2022
 *
 *************************************************************************/

#include <doonce.h>

#include <dooncemanager.h>

#include <QDebug>

using namespace std;
using namespace BT;


// ---- DoOnce class ----

DoOnce::DoOnce(DoOnceManager &manager, const string &name, const NodeConfiguration &config)
    : DecoratorNode(name, config), m_manager(manager)
{}

DoOnce::~DoOnce()
{
    m_manager.removeNode(m_id);
}

void DoOnce::reset()
{
    m_finishedOnce = false;
}

BT::PortsList DoOnce::providedPorts()
{
    return {InputPort<string>("id")};
}


BT::NodeStatus DoOnce::tick()
{
    if (m_id.empty()) {
        auto id = getInput<string>("id");
        if (!id)
            throw RuntimeError("Missing parameter [id] in DoOnce node");

        m_id = id.value();
        m_manager.addDoOnceNode(m_id, *this);
    }

    setStatus(NodeStatus::RUNNING);

    if (m_finishedOnce)
        return NodeStatus::FAILURE;

    auto childStatus = child_node_->executeTick();
    if (childStatus == NodeStatus::SUCCESS || childStatus == NodeStatus::FAILURE) {
        m_finishedOnce = true;
    }
    return childStatus;
}


// ---- ResetDoOnce class ----

ResetDoOnce::ResetDoOnce(DoOnceManager &manager,
                         const std::string &name,
                         const BT::NodeConfiguration &config)
    : SyncActionNode(name, config), m_manager(manager)
{}

PortsList ResetDoOnce::providedPorts()
{
    return {InputPort<string>("id")};
}

NodeStatus ResetDoOnce::tick()
{
    auto id = getInput<string>("id");
    if (!id)
        throw RuntimeError("Missing parameter [id] in ResetDoOnce node");

    return m_manager.resetNode(id.value()) ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
}
