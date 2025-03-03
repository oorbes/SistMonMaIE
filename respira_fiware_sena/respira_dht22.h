/**
 * Copyright (c) 2019 panStamp <contact@panstamp.com>
 * 
 * This file is part of the RESPIRA project.
 * 
 * panStamp  is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * any later version.
 * 
 * panStamp is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with panStamp; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
 * USA
 * 
 * Author: Daniel Berenguer
 * Creation date: Sep 6 2019
 */

#ifndef _RESPIRA_DTH22_H
#define _RESPIRA_DHT22_H
#include <DHT.h>
#define DHTTYPE DHT22
#define DHTPIN 13

//#include "SparkFun_Si7021_Breakout_Library.h"

/**
 * Return codes
 */
#define RESPIRA_DHT22_OK  0

class RESPIRA_DHT22
{
  private:
    /**
     * Sensor object
     */
    //Weather htu;
    DHT *htu;
    /**
     * Average temperature in ºC
     */
    float avgTemperature;

    /**
     * Average humidity in %
     */
    float avgHumidity;

    /**
     * Number of samples for the calculation of the averages
     */
    uint16_t avgSamples;

  public:
    /**
     * Class constructor
     */
    inline RESPIRA_DHT22(void)
    {
      htu=new DHT(DHTPIN, DHTTYPE);
      resetAvg();
    }

    /**
     * begin
     * 
     * Initialize sensor board
     * 
     * @return return code
     */
    inline uint8_t begin(void)
    {
      // Initialize sensor
      htu->begin();

      return RESPIRA_DHT22_OK;
    }

    /**
     * read
     * 
     * Request reading and read response from sensor
     *
     * @return Return code
     */
    inline uint8_t read(void)
    {
      float temperature = htu->readTemperature();
      float humidity = htu->readHumidity();

      Serial.print("DHT22 : Temperature = "); Serial.print(temperature); Serial.print(" ºC - ");
      Serial.print("Humidity = "); Serial.print(humidity); Serial.println(" %");
      
      // Update averages
      avgTemperature += temperature;
      avgHumidity += humidity;
      avgSamples++;

      return RESPIRA_DHT22_OK;
    }

    /**
     * getTemperature
     * 
     * Get instant temperature in ºC
     * 
     * @return temperature in ºC
     */
    inline float getTemperature(void)
    {
      return htu->readTemperature();
    }

    /**
     * getHumidity
     * 
     * Get instant humidity in º%
     * 
     * @return Relative humidity in %
     */
    inline float getHumidity(void)
    {
      return htu->readHumidity();
    }

    /**
     * getAvgTemperature
     * 
     * Get average temperature
     * 
     * @return Average temperature in ºC
     */
    inline float getAvgTemperature(void)     
    {
      if (avgSamples == 0)
        return 0.0;
       
      return avgTemperature / avgSamples;
    }

    /**
     * getAvgHumidity
     * 
     * Get average humidity
     * 
     * @return Average humidity in %
     */
    inline float getAvgHumidity(void)
    {
      if (avgSamples == 0)
        return 0.0;
       
      return avgHumidity / avgSamples;
    }

    /**
     * resetAvg
     * 
     * Reset average variables
     */
    inline void resetAvg(void)
    {
      avgTemperature = 0;
      avgHumidity = 0;
      avgSamples = 0;
    }
};
#endif

