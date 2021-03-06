/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/03/2022
 *
 *************************************************************************/

#include <usobstacledetector.h>

using namespace std;


USObstacleDetector::USObstacleDetector(std::shared_ptr<IUSSensor> usSensor, QObject *parent)
    : IUSObstacleDetector(parent), m_sensor(usSensor)
{
    connect(m_sensor.get(),
            &IUSSensor::distanceChanged,
            this,
            &USObstacleDetector::checkDistWithThresholds);
}

USObstacleDetector::~USObstacleDetector() {}

void USObstacleDetector::addThreshold(float threshold)
{
    const auto itr = find(begin(m_thresholds), end(m_thresholds), threshold);
    if (itr != end(m_thresholds))
        return;

    m_thresholds.push_back(threshold);
    sort(begin(m_thresholds), end(m_thresholds));
}

void USObstacleDetector::removeThreshold(int index)
{
    if (index < 0 || index >= m_thresholds.size())
        return;

    m_thresholds.erase(begin(m_thresholds) + index);
}

const std::vector<float> &USObstacleDetector::thresholds() const
{
    return m_thresholds;
}

void USObstacleDetector::checkDistWithThresholds()
{
    if (m_previousDistance > 0) {
        for (auto itr = begin(m_thresholds); itr != end(m_thresholds); ++itr) {
            const auto threshold = *itr;
            const auto index = distance(begin(m_thresholds), itr);
            if (m_sensor->distance() < threshold && m_previousDistance > threshold) {
                emit thresholdCrossed(index, true);
            } else if (m_sensor->distance() > threshold && m_previousDistance < threshold) {
                emit thresholdCrossed(index, false);
            }
        }
    }

    m_previousDistance = m_sensor->distance();
}

