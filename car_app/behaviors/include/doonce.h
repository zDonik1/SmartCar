/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 20/03/2022
 *
 *************************************************************************/

#pragma once

#include <behaviortree_cpp_v3/decorator_node.h>
#include <behaviortree_cpp_v3/action_node.h>

class DoOnceManager;

class DoOnce : public BT::DecoratorNode
{
public:
    DoOnce(DoOnceManager &manager, const std::string &name, const BT::NodeConfiguration &config);
    virtual ~DoOnce() override;

    void reset();

    static BT::PortsList providedPorts();

protected:
    virtual BT::NodeStatus tick() override;

private:
    DoOnceManager &m_manager;
    std::string m_id;
    bool m_finishedOnce = false;
};

class ResetDoOnce : public BT::SyncActionNode
{
public:
    ResetDoOnce(DoOnceManager &manager,
                const std::string &name,
                const BT::NodeConfiguration &config);

    static BT::PortsList providedPorts();

protected:
    virtual BT::NodeStatus tick() override;

private:
    DoOnceManager &m_manager;
};
