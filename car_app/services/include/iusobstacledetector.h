/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 04/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>


class IUSObstacleDetector : public QObject
{
    Q_OBJECT

public:
    explicit IUSObstacleDetector(QObject *parent = nullptr) : QObject(parent) {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual void addThreshold(float threshold) = 0;
    virtual void removeThreshold(int index) = 0;
    virtual const std::vector<float> &thresholds() const = 0;

signals:
    /** less is true when distance is less than threshold */
    void thresholdCrossed(int index, bool less);
};
