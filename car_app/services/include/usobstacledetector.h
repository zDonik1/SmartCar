/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <QElapsedTimer>

#include <iusobstacledetector.h>
#include <iussensor.h>

class USObstacleDetector : public IUSObstacleDetector
{
    Q_OBJECT

public:
    USObstacleDetector(std::shared_ptr<IUSSensor> usSensor, QObject *parent = nullptr);
    virtual ~USObstacleDetector();

    virtual void start() override;
    virtual void stop() override;
    virtual void addThreshold(float threshold) override;
    virtual void removeThreshold(int index) override;
    virtual const std::vector<float> &thresholds() const override;

private slots:
    void checkDistWithThresholds();

private:
    std::shared_ptr<IUSSensor> m_sensor;
    std::vector<float> m_thresholds;
    QElapsedTimer m_elapsedTimer;
    float m_previousDistance = -1;
};
