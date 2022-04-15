/*
 * misc_fns.cpp
 *
 * Assorted dummy functions I'm calling from the menu to demonstrate
 * how to use it etc.
 *
 */

#include "global.h"
#include "misc_fns.h"

/*
 * Reset the CPU
 */
void resetProcessor()
{
    Serial.println("A restart was initiated!");
    Serial.println("I will restart in 8 Seconds...");
    int countdownMS = Watchdog.enable(8000); // WatchDog timeout in 8 seconds
    delay(countdownMS + 1000);               // Wait for 9 second!!!
    Watchdog.disable();                      // The WatchDog WILL time out and therefore restart the CPU
}

/*
 * Toggle the debugging status
 */
void toggleDebug()
{
    menuClearScreen();
    if (DebugNormalOperation == false)
    {
        Serial.println("Debugs ENABLED");
        DebugNormalOperation = true;
        delay(2000);
    }
    else
    {
        Serial.println("Debugs disabled");
        DebugNormalOperation = false;
        delay(2000);
    }
}

/*
 *  Display the current status of the Arduino itself.
 */
void arduinoStatus()
{
    Serial.println("Arduino Status");
    Serial.println("==============");
    Serial.print("Hostname:");
    Serial.println(ArduinoHostname);
    Serial.print("Password:");
    Serial.println(ArduinoPassword);
    Serial.print("SSID:");
    Serial.println(ArduinoSSID);
    Serial.print("Key:");
    Serial.println(ArduinoKEY);
}

/*
 * Show the dummy Temp and Humidity values.
 */
void showTempHumid()
{
    Serial.println("Read from SHT35 temperature & humidity sensor...");
    Serial.print("Temperature °C = ");
    Serial.println(Temp);
    Serial.print("Humidity % = ");
    Serial.println(Humi);
}

/*
 * Ask the user for WiFi SSID and Key
 */
void setWiFi()
{
    Serial.println("You can change the Arduino WiFi setup now.");
    Serial.println();
    Serial.print("WiFi SSID: ");
    ArduinoSSID = menuSerRx(true);
    Serial.println();
    Serial.print("WiFi  Key: ");
    ArduinoKEY = menuSerRx(true);
    Serial.println();
    Serial.println();
    Serial.println("WiFi parameters gathered successfully!");
    delay(2000);
}

/*
 * Ask the user for the hostname
 */
void setHostname()
{
    Serial.println("You can change the Arduino name now.");
    Serial.println("The maximum length is 32 characters...");
    Serial.println();
    Serial.print("Arduino Name: ");
    ArduinoHostname = menuSerRx(true);
    Serial.println();
    Serial.println("The Arduino name was gathered successfully!");
    delay(2000);
}

/*
 * Ask the user for the password
 */
void setPw()
{
    const int MaxPw = 32;
    const int MinPw = 6;

StartAgainCPW:
    String FirPassword;
    String SecPassword;
    Serial.println("Change the Arduino Menu password.");
    Serial.print("The password length must be between ");
    Serial.print(MinPw);
    Serial.print(" and ");
    Serial.print(MaxPw);
    Serial.println(" characters...");
    Serial.println("");
    Serial.print(" New password: ");
    FirPassword = menuSerRx(false);
    if (FirPassword.length() < MinPw)
    {
        Serial.println("");
        Serial.print(" Too short...");
        delay(2000);
        goto StartAgainCPW;
    }
    else if (FirPassword.length() > MaxPw)
    {
        Serial.println("");
        Serial.print(" Too long...");
        delay(2000);
        goto StartAgainCPW;
    }
    else
    {
        Serial.println("");
        Serial.print("Retype new pw: ");
        SecPassword = menuSerRx(false);
        if (FirPassword != SecPassword)
        {
            Serial.println("");
            Serial.println("The new password was not consistent!");
            delay(2000);
            goto StartAgainCPW;
        }
        else
        {
            ArduinoPassword = SecPassword;
            Serial.println("");
            Serial.println("The password was accepted!");
            Serial.println("");
            Serial.println("The new password was stored successfully!");
            delay(2000);
        }
    }
}

// END - misc_fns.cpp