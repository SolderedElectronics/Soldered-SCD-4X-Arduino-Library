/**
 * @file          Example3_DisableAutoCalibration.ino
 *
 * @brief         Disable Auto Calibration. This example prints the current CO2 level, relative humidity, and
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
    // Please see the next example for a full description of skipStopPeriodicMeasurements

    // In this example, we call .begin and set autoCalibrate to false to disable automatic calibration
    if (mySensor.begin(true, false) == false)
    // measBegin_________/     |
    // autoCalibrate__________/
    {
        Serial.println(F("Sensor did not begin correctly. Please check wiring. Freezing..."));
        while (1)
            ;
    }
}

void loop()
{
    // readMeasurement will return true when fresh data is available
    if (mySensor.readMeasurement()) 
    {
        // Print all data to the Serial Monitor
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
    {
        // If the data isn't available, it will print dots on the serial monitor
        Serial.print(F("."));
    }

    // Wait a bit
    delay(500);
}
