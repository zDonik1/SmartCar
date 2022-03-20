/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 17/03/2022
 *
 *************************************************************************/

#pragma once

#include <behaviortree_cpp_v3/action_node.h>

#include <imovement.h>
#include <iavoider.h>

class Avoid : public BT::StatefulActionNode
{
public:
    Avoid(std::shared_ptr<IMovement> movement,
          std::shared_ptr<IAvoider> avoider,
          const std::string &name,
          const BT::NodeConfiguration &config);

    virtual BT::NodeStatus onStart() override;
    virtual BT::NodeStatus onRunning() override;
    virtual void onHalted() override;

private:
    std::shared_ptr<IMovement> m_movement;
    std::shared_ptr<IAvoider> m_avoider;
};
