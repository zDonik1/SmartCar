/**************************************************************************
 *
 *   @author Doniyorbek Tokhirov <tokhirovdoniyor@gmail.com>
 *   @date 16/03/2022
 *
 *************************************************************************/

#pragma once


/**
 * @brief ISensor is a general interface for any sensors that can give back readings.
 * The sensors can be started or stopped, and while running, they give back reading after specific
 * period of time. Readings can also be manually requested, only when start(0) is called when
 * starting the sensor. The readings cannot be taken manually unless the sensor has been started.
 */
class ISensor
{
public:
    /**
     * @brief Starts the sensor.
     * @param Update interval defines how fast the readings should be updated in milliseconds.
     * If the update interval is set to 0, readings should be requested manually.
     */
    virtual void start(int updateInterval) = 0;

    virtual void stop() = 0;

    /**
     * @brief Manually requests a reading and won't work while the sensor is running (after start
     * has been called). The readings cannot be taken manually unless the sensor has been started.
     */
    virtual void requestReading() = 0;
};
