/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>


class IUSSensor : public QObject
{
    Q_OBJECT

public:
    explicit IUSSensor(QObject *parent = nullptr) : QObject(parent) {}

    virtual void start() = 0;
    virtual void stop() = 0;
    virtual float distance() = 0;
    virtual void setThreshold(float distance) = 0;

signals:
    /** less is true when distance is less than threshold */
    void thresholdCrossed(bool less);
};
