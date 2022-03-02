/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 02/03/2022
 *
 *************************************************************************/

#pragma once

#include <memory>

#include <QTimer>
#include <QThread>

#include <iussensor.h>


class USThread;

class USSensor : public IUSSensor
{
    Q_OBJECT

public:
    explicit USSensor(int trigPinN, int echoPinN, QObject *parent = nullptr);
    virtual ~USSensor();

    virtual void start() override;
    virtual void stop() override;
    virtual float distance() override;
    virtual void setThreshold(float threshold) override;

private slots:
    void onDistanceReady(float distance);

private:
    std::unique_ptr<USThread> m_thread;
    float m_distance = -1;
    float m_threshold = -1;
    float m_previousDistance = -1;
};
