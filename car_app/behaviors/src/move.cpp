/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 17/03/2022
 *
 *************************************************************************/

#include <move.h>

using namespace std;
using namespace BT;

// ---- Move class ----

Move::Move(std::shared_ptr<IMovement> movement,
           const std::string &name,
           const BT::NodeConfiguration &config)
    : StatefulActionNode(name, config), m_movement(movement)
{}

PortsList Move::providedPorts()
{
    return {InputPort<Vector>("vector"), InputPort<unsigned int>("duration")};
}

NodeStatus Move::onStart()
{
    auto vector = getInput<Vector>("vector");
    if (!vector)
        throw RuntimeError("Missing parameter [vector] in Move node");

    auto duration = getInput<unsigned int>("duration");
    if (duration || duration.value() == 0) {
        return NodeStatus::SUCCESS;
    } else {
        m_movement->move(vector.value());
        return NodeStatus::RUNNING;
    }
}

NodeStatus Move::onRunning()
{
    auto duration = getInput<unsigned int>("duration");
    if (duration && m_elapsedTimer.elapsed() >= duration.value()) {
        m_movement->stop();
        return NodeStatus::SUCCESS;
    }
    return NodeStatus::RUNNING;
}

void Move::onHalted()
{
    m_movement->stop();
}

// ---- Stop class ----

Stop::Stop(std::shared_ptr<IMovement> movement, const std::string &name)
    : SyncActionNode(name, {}), m_movement(movement)
{}

NodeStatus Stop::tick()
{
    m_movement->stop();
    return NodeStatus::SUCCESS;
}
