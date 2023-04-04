/**
 * @file          Example2_LowPowerReadings.ino
 *
 * @brief         Reading CO2, humidity and temperature from the SCD4x in Low Power mode
 *
 *                Hardware Connections:
 *                Attach Dasduino to computer using a USB cable.
 *                Connect SCD40/41 to Dasduino using easyC cable.
 *                Open Serial Monitor at 115200 baud.
 *
 * @author        Paul Clark
 *                Based on earlier code by: Nathan Seidle
 *                Modified by Soldered
 *
 * @link          solde.red/333191, solde.red/333220
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

    // mySensor.enableDebugging(); // Uncomment this line to get helpful debug messages on Serial

    //.begin will start periodic measurements for us (see the later examples for details on how to override this)
    if (mySensor.begin() == false)
    {
        Serial.println(F("Sensor not detected. Please check wiring. Freezing..."));
        while (1)
            ;
    }

    // By default, the SCD4x has data ready every five seconds.
    // We can enable low power operation and receive a reading every ~30 seconds

    // But first, we need to stop periodic measurements otherwise startLowPowerPeriodicMeasurement will fail
    if (mySensor.stopPeriodicMeasurement() == true)
    {
        Serial.println(F("Periodic measurement is disabled!"));
    }

    // Now we can enable low power periodic measurements
    if (mySensor.startLowPowerPeriodicMeasurement() == true)
    {
        Serial.println(F("Low power mode enabled!"));
    }

    // The SCD4x has data ready every thirty seconds
}

void loop()
{
    if (mySensor.readMeasurement()) // readMeasurement will return true when fresh data is available
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

    delay(1000);
}
