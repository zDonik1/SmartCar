/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 05/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <iirvectorservice.h>
#include <iirsensor.h>


class DoubleLineTracer : public IIRVectorService
{
public:
    DoubleLineTracer(std::shared_ptr<IIRSensor> leftSensor,
                     std::shared_ptr<IIRSensor> rightSensor,
                     QObject *parent = nullptr);

    virtual const Vector &vector() const override;

private slots:
    void sensorsUpdated();

private:
    std::shared_ptr<IIRSensor> m_leftSensor;
    std::shared_ptr<IIRSensor> m_rightSensor;
    Vector m_vector;
};
