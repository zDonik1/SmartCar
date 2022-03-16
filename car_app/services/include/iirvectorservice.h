/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 07/03/2022
 *
 *************************************************************************/

#pragma once

#include <QObject>

#include <vector.h>


class IIRVectorService : public QObject
{
    Q_OBJECT

public:
    explicit IIRVectorService(QObject *parent = nullptr) : QObject(parent) {}

    virtual const Vector &vector() const = 0;

signals:
    void vectorChanged();
};
