/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <ilinetracer.h>
#include <iirsensor.h>


class DoubleLineTracer : public ILineTracer
{
public:
    DoubleLineTracer(std::unique_ptr<IIRSensor> leftSensor,
                     std::unique_ptr<IIRSensor> rightSensor,
                     QObject *parent = nullptr);

    virtual void start() override;
    virtual void stop() override;
    virtual const Vector &vector() const override;

private slots:
    void sensorsUpdated();

private:
    std::unique_ptr<IIRSensor> m_leftSensor;
    std::unique_ptr<IIRSensor> m_rightSensor;
    Vector m_vector;
};