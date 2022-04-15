/*
 *  setup.cpp
 */

#include "global.h"

void setup()
{
    pinMode(LED_BUILTIN, OUTPUT);   // Initialise LED pin

    // Initialise my dummy parameters.
    ArduinoPassword = "password";
    ArduinoHostname = "Arduino01";
    ArduinoSSID = "homessid";
    ArduinoKEY = "wifikeywifi";
    Temp = 20;
    Humi = 35;
    
    // Initialise the serial interface and wait for port to open:
    Serial.begin(115200);
    delay(5000);
    Serial.println("Serial Service Menu Tester - Running...");
    Serial.println("Press 'm' to open the menu");
    delay(2000);
}