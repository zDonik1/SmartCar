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


class USWorker;

class USSensor : public IUSSensor
{
    Q_OBJECT

public:
    explicit USSensor(int trigPinN, int echoPinN, QObject *parent = nullptr);
    virtual ~USSensor();

    virtual void start(int updateInterval) override;
    virtual void stop() override;

    virtual void requestReading() override;
    virtual float distance() const override;

private:
    std::unique_ptr<USWorker> m_worker;
    QThread m_thread;
    float m_distance = -1;
    bool m_isRunning = false;
    bool m_manualRequestMode = false;
};
