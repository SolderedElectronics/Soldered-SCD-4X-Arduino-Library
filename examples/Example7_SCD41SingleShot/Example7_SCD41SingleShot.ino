/**
 * @file          Example1_BasicReadings.ino
 * 
 * @brief         SCD41 Low Power Single Shot. This example prints the current CO2 level, relative humidity, and temperature in C.
 * 
 * @author        Paul Clark
 *                Based on earlier code by: Nathan Seidle
 *                Modified by Soldered
 * 
 * @link          solde.red/333191, solde.red/333220
 * 
 * @note          Hardware Connections:
 *                Attach Dasduino to computer using a USB cable.
 *                Connect SCD40/41 to Dasduino using easyC cable.
 *                Open Serial Monitor at 115200 baud.
 *
 * License: MIT. See license file for more information but you can
 * basically do whatever you want with this code.
 */

#include <Wire.h>

#include "SCD-4X-SOLDERED.h" // Click here to get the library: https://github.com/SolderedElectronics/Soldered-SCD-4X-Arduino-Library

SCD_4X mySensor(SCD4x_SENSOR_SCD41); // Tell the library we have a SCD41 connected

void setup()
{
  Serial.begin(115200);
  Serial.println(F("SCD41 Example"));
  Wire.begin();

  //mySensor.enableDebugging(); // Uncomment this line to get helpful debug messages on Serial

  if (mySensor.begin(false, true, false) == false) // Do not start periodic measurements
  //measBegin_________/     |     |
  //autoCalibrate__________/      |
  //skipStopPeriodicMeasurements_/
  {
    Serial.println(F("Sensor not detected. Please check wiring. Freezing..."));
    while (1)
      ;
  }

  //Let's call measureSingleShot to start the first conversion
  bool success = mySensor.measureSingleShot();
  if (success == false)
  {
    Serial.println(F("measureSingleShot failed. Are you sure you have a SCD41 connected? Freezing..."));
    while (1)
      ;    
  }
}

void loop()
{
  while (mySensor.readMeasurement() == false) // readMeasurement will return true when fresh data is available
  {
    Serial.print(F("."));
    delay(500);
  }

  Serial.println();

  Serial.print(F("CO2(ppm):"));
  Serial.print(mySensor.getCO2());

  Serial.print(F("\tTemperature(C):"));
  Serial.print(mySensor.getTemperature(), 1);

  Serial.print(F("\tHumidity(%RH):"));
  Serial.print(mySensor.getHumidity(), 1);

  Serial.println();
  
  mySensor.measureSingleShotRHTOnly(); // Request just the RH and the Temperature (should take 50ms)

  while (mySensor.readMeasurement() == false) // readMeasurement will return true when fresh data is available
  {
    Serial.print(F("."));
    delay(5);
  }

  Serial.println();

  Serial.print(F("Temperature(C):"));
  Serial.print(mySensor.getTemperature(), 1);

  Serial.print(F("\tHumidity(%RH):"));
  Serial.print(mySensor.getHumidity(), 1);

  Serial.println();
  
  mySensor.measureSingleShot(); // Request fresh data (should take 5 seconds)
}
