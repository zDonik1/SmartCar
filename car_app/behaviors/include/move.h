/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 17/03/2022
 *
 *************************************************************************/

#pragma once

#include <QElapsedTimer>

#include <behaviortree_cpp_v3/action_node.h>

#include <imovement.h>
#include <customporttypes.h>


class Move : public BT::StatefulActionNode
{
public:
    Move(std::shared_ptr<IMovement> movement,
         const std::string &name,
         const BT::NodeConfiguration &config);

    static BT::PortsList providedPorts();

    virtual BT::NodeStatus onStart() override;
    virtual BT::NodeStatus onRunning() override;
    virtual void onHalted() override;

private:
    std::shared_ptr<IMovement> m_movement;
    QElapsedTimer m_elapsedTimer;
};


class Stop : public BT::SyncActionNode
{
public:
    Stop(std::shared_ptr<IMovement> movement, const std::string &name);

    virtual BT::NodeStatus tick() override;

private:
    std::shared_ptr<IMovement> m_movement;
};
