/**
 * @file          Example6_SelfTest_FactoryReset.ino
 *
 * @brief         Self Test and Factory Reset. This example prints the current CO2 level, relative humidity, and
 *                temperature in C.
 *
 *                Hardware Connections:
 *                Attach Dasduino to computer using a USB cable.
 *                Connect SCD40/41 to Dasduino using easyC cable.
 *                Open Serial Monitor at 115200 baud.
 *
 * @authors       Paul Clark
 *                Based on earlier code by: Nathan Seidle
 *                Modified by Soldered
 *
 * @link          solde.red/333191, solde.red/333220
 *
 * License: MIT. See license file for more information but you can
 * basically do whatever you want with this code.
 */

// Include Wire library for I2C communication
#include "Wire.h"

// Include Soldered library for SCD40/SCD41 sensor
#include "SCD-4X-SOLDERED.h" // Click here to get the library: https://github.com/SolderedElectronics/Soldered-SCD-4X-Arduino-Library

// Create object for SCD sensor
SCD_4X mySensor;

void setup()
{
    // Init serial and I2C communication
    Serial.begin(115200);
    Serial.println(F("SCD4x Example"));
    Wire.begin();

    // mySensor.enableDebugging(); // Uncomment this line to get helpful debug messages on Serial

    if (mySensor.begin() == false)
    {
        Serial.println(F("Sensor not detected. Please check wiring. Freezing..."));
        while (1)
            ;
    }

    // We need to stop periodic measurements before we can run the self test
    if (mySensor.stopPeriodicMeasurement() == true)
    {
        Serial.println(F("Periodic measurement is disabled!"));
    }

    // Now we can run the self test:
    Serial.println(F("Starting the self-test. This will take 10 seconds to complete..."));

    bool success = mySensor.performSelfTest();

    Serial.print(F("The self test was "));
    if (success == false)
        Serial.print(F("not "));
    Serial.println(F("successful"));

    // We can do a factory reset if we want to completely reset the sensor
    Serial.println(F("Starting the factory reset. This will take 1200ms seconds to complete..."));

    success = mySensor.performFactoryReset();

    Serial.print(F("The factory reset was "));
    if (success == false)
        Serial.print(F("not "));
    Serial.println(F("successful"));
}

void loop()
{
    // Nothing to do here
}
