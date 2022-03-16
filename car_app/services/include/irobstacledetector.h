/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 08/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <iirvectorservice.h>
#include <iirsensor.h>


class IRObstacleDetector : public IIRVectorService
{
public:
    IRObstacleDetector(std::shared_ptr<IIRSensor> leftSensor,
                       std::shared_ptr<IIRSensor> rightSensor,
                       QObject *parent = nullptr);

    virtual const Vector &vector() const override;

private slots:
    void sensorsUpdated();

private:
    void setVector(Vector vector);

private:
    std::shared_ptr<IIRSensor> m_leftSensor;
    std::shared_ptr<IIRSensor> m_rightSensor;
    Vector m_vector;
};
