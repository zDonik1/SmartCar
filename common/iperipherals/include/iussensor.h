/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <isensor.h>

class IUSSensor : public QObject, public ISensor
{
    Q_OBJECT

public:
    explicit IUSSensor(QObject *parent = nullptr);

    virtual float distance() const = 0;

Q_SIGNALS:
    void distanceChanged();
};
