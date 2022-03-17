/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <iavoider.h>
#include <iirsensor.h>


class DoubleLineTracer : public IAvoider
{
public:
    DoubleLineTracer(std::shared_ptr<IIRSensor> leftSensor,
                     std::shared_ptr<IIRSensor> rightSensor,
                     QObject *parent = nullptr);

    virtual const Vector &vector() const override;
    virtual bool isBlocked() const override;

private slots:
    void sensorsUpdated();

private:
    void setVector(Vector vector);
    void setIsBlocked(bool isBlocked);

private:
    std::shared_ptr<IIRSensor> m_leftSensor;
    std::shared_ptr<IIRSensor> m_rightSensor;
    Vector m_vector;
    bool m_isBlocked = false;
};
