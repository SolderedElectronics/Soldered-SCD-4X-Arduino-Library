/**
 **************************************************
 *
 * @file        SCD-4X-SOLDERED.h
 * @brief       Header file for Soldered SCD-4X Arduino library.
 *
 *
 * @copyright   GNU General Public License v3.0
 * @authors     Karlo Leksic for soldered.com
 ***************************************************/

#ifndef __SCD4X__
#define __SCD4X__

#include "Arduino.h"
#include "libs/SparkFun_SCD4x_Arduino_Library/src/SparkFun_SCD4x_Arduino_Library.h"

class SCD_4X : public SCD4x
{
  public:
    SCD_4X(scd4x_sensor_type_e sensorType = SCD4x_SENSOR_SCD40);

  protected:
  private:
};

#endif
