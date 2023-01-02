/**
 * @file          Example4_SkipStopPeriodicMeasurement.ino
 * 
 * @brief         Skip Stop Periodic Measurement. This example prints the current CO2 level, relative humidity, and temperature in C.
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
SCD_4X mySensor;

void setup()
{
  Serial.begin(115200);
  Serial.println(F("SCD4x Example"));
  Wire.begin();

  //mySensor.enableDebugging(); // Uncomment this line to get helpful debug messages on Serial

  //.begin has three boolean parameters:
  //  measBegin: set to true to begin periodic measurements automatically;
  //             set to false to leave periodic measurements disabled.
  //             Default is true.
  //  autoCalibrate: set to true to leave automatic calibration enabled;
  //                 set to false to disable automatic calibration.
  //                 Default is true.
  //  skipStopPeriodicMeasurements: set to true to make .begin skip the initial call of stopPeriodicMeasurement;
  //                                set to false to make .begin stop periodic measurements before doing anything else.
  //                                Default is false.
  //When periodic measurements are enabled, the SCD4x will only repond to:
  //  readMeasurement; stopPeriodicMeasurement; setAmbientPressure; and getDataReadyStatus. All other commands are ignored.
  //  Because .begin uses getSerialNumber to check if the SCD4x is connected, .begin would fail if a previous example had
  //  left periodic measurements enabled. So, by default, .begin will call stopPeriodicMeasurement before calling
  //  getSerialNumber. The down side to this is that stopPeriodicMeasurement takes 500ms to complete, incorporating a
  //  blocking call of delay(500). If the user is confident that periodic measurements are already disabled,
  //  skipStopPeriodicMeasurements can be set to true to skip the initial call of stopPeriodicMeasurement.
  //In this example, we will tell .begin to: enable periodic measurements; enable auto calibration;
  //  and skip the initial stopPeriodicMeasurement to save that 500ms delay.
  //Instead we can manually call stopPeriodicMeasurement first:

  //It is OK to call stopPeriodicMeasurement before .begin. It will default to using Wire.
  //You can specify a different I2C interface by calling e.g.: mySensor.stopPeriodicMeasurement(500, Wire1)
  if (mySensor.stopPeriodicMeasurement() == false) 
  {
    Serial.println(F("Could not stop periodic measurements. Is the sensor connected? Please check wiring. Freezing..."));
    while (1)
      ;
  }

  //Now we can call .begin and set skipStopPeriodicMeasurements to true
  if (mySensor.begin(true, true, true) == false)
  //measBegin_________/     |     |
  //autoCalibrate__________/      |
  //skipStopPeriodicMeasurements_/
  {
    Serial.println(F("Sensor did not begin correctly. Please check wiring. Freezing..."));
    while (1)
      ;
  }
}

void loop()
{
  if (mySensor.readMeasurement()) // readMeasurement will return true when fresh data is available
  {
    Serial.println();

    Serial.print(F("CO2(ppm):"));
    Serial.print(mySensor.getCO2());

    Serial.print(F("\tTemperature(C):"));
    Serial.print(mySensor.getTemperature(), 1);

    Serial.print(F("\tHumidity(%RH):"));
    Serial.print(mySensor.getHumidity(), 1);

    Serial.println();
  }
  else
    Serial.print(F("."));

  delay(500);
}
