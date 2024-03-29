/**
 * @file          Example5_SignalCompensation.ino
 *
 * @brief         Signal Compensation. This example prints the current CO2 level, relative humidity, 
 *                and temperature in *C.
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

    // We need to stop periodic measurements before we can change the sensor signal compensation settings
    if (mySensor.stopPeriodicMeasurement() == true)
    {
        Serial.println(F("Periodic measurement is disabled!"));
    }

    // Now we can change the sensor settings.
    // There are three signal compensation commands we can use: setTemperatureOffset; setSensorAltitude; and
    // setAmbientPressure

    Serial.print(F("Temperature offset is currently: "));
    Serial.println(mySensor.getTemperatureOffset(), 2); // Print the temperature offset with two decimal places
    mySensor.setTemperatureOffset(5);                   // Set the temperature offset to 5C
    Serial.print(F("Temperature offset is now: "));
    Serial.println(mySensor.getTemperatureOffset(), 2); // Print the temperature offset with two decimal places

    Serial.print(F("Sensor altitude is currently: "));
    Serial.println(mySensor.getSensorAltitude()); // Print the sensor altitude
    mySensor.setSensorAltitude(1000);             // Set the sensor altitude to 1000m
    Serial.print(F("Sensor altitude is now: "));
    Serial.println(mySensor.getSensorAltitude()); // Print the sensor altitude

    // There is no getAmbientPressure command
    bool success = mySensor.setAmbientPressure(98700); // Set the ambient pressure to 98700 Pascals
    if (success)
    {
        Serial.println(F("setAmbientPressure was successful"));
    }

    // The signal compensation settings are stored in RAM by default and will reset if reInit is called
    // or if the power is cycled. To store the settings in EEPROM we can call:
    mySensor.persistSettings(); // Uncomment this line to store the sensor settings in EEPROM

    // Just for giggles, while the periodic measurements are stopped, let's read the sensor serial number
    char serialNumber[13]; // The serial number is 48-bits. We need 12 bytes plus one extra to store it as ASCII Hex
    if (mySensor.getSerialNumber(serialNumber) == true)
    {
        Serial.print(F("The sensor's serial number is: 0x"));
        Serial.println(serialNumber);
    }

    // Finally, we need to restart periodic measurements
    if (mySensor.startPeriodicMeasurement() == true)
    {
        Serial.println(F("Periodic measurements restarted!"));
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
