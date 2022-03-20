/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 20/03/2022
 *
 *************************************************************************/

#pragma once

#include <behaviortree_cpp_v3/condition_node.h>

#include <iavoider.h>


class AvoiderNotBlocked : public BT::ConditionNode
{
public:
    AvoiderNotBlocked(std::shared_ptr<IAvoider> avoider,
                      const std::string &name,
                      const BT::NodeConfiguration &config);

protected:
    virtual BT::NodeStatus tick() override;

private:
    std::shared_ptr<IAvoider> m_avoider;
};
