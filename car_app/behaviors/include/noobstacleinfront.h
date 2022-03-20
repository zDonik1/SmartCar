/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 20/03/2022
 *
 *************************************************************************/

#pragma once

#include <behaviortree_cpp_v3/condition_node.h>

#include <iussensor.h>


class NoObstacleInFront : public BT::ConditionNode
{
public:
    NoObstacleInFront(std::shared_ptr<IUSSensor> sensor,
                      const std::string &name,
                      const BT::NodeConfiguration &config);

    static BT::PortsList providedPorts();

protected:
    virtual BT::NodeStatus tick() override;

private:
    std::shared_ptr<IUSSensor> m_sensor;
};
