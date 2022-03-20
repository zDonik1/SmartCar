/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 20/03/2022
 *
 *************************************************************************/

#include <noobstacleinfront.h>

using namespace std;
using namespace BT;

NoObstacleInFront::NoObstacleInFront(shared_ptr<IUSSensor> sensor,
                                     const string &name,
                                     const NodeConfiguration &config)
    : ConditionNode(name, config), m_sensor(sensor)
{}

PortsList NoObstacleInFront::providedPorts()
{
    return {InputPort<unsigned int>("threshold")};
}

NodeStatus NoObstacleInFront::tick()
{
    auto threshold = getInput<unsigned int>("threshold");
    if (!threshold)
        throw RuntimeError("Missing parameter [threshold] in NoObstacleInFront node");

    if (m_sensor->distance() < 0)
        return NodeStatus::SUCCESS;

    return m_sensor->distance() > threshold.value() ? NodeStatus::SUCCESS : NodeStatus::FAILURE;
}
