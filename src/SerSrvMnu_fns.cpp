
/*
 * SerSrvMnu_fns.cpp
 *
 * Functions that support the Serial Service Menu capability
 * from https://create.arduino.cc/projecthub/andreas_waldherr/serial-service-menu-91c5c1
 * with slight mods by me (p.jeffress)
 *
 */

#include "global.h"
#include "SerSrvMnu_fns.h"

/*
 * Check for menu start key and if detected,
 * then display the menu.
 */
void menuDo()
{
    char rc; // char we read into

    // If 'm' was detected, then start the menus
    if (SerSess == false && Serial.available())
    {
        rc = Serial.read();
        if (rc == 'm')
        {
            Serial.println();
            Serial.println("loop() paused - entering menu system");
            SerSess = true; // flag that the serial session is established
        }
    }

    // If a session was established, display the Service Menu and get the users input
    while (SerSess == true)
    {
        printMenu();                         // Display the Menu
        String MenuChoice = menuSerRx(true); // Wait for the selection
        Serial.println();
        Serial.println();

        if (MenuChoice == "1")
        {
            menuClearScreen();
            arduinoStatus();
            menuGoBack();   // display [0] to exit msg and wait
        }
        else if (MenuChoice == "2")
        {
            menuClearScreen();
            resetProcessor();
        }
        else if (MenuChoice == "3")
        {
            // We have wrapped this menu item with the option for user to
            // refresh or return to main menu.
            bool stay = true; // run the while loop at least once.
            while (stay == true)
            {
                menuClearScreen();
                showTempHumid();
                stay = menuGoBackOrRefresh();
            }
        }
        else if (MenuChoice == "4")
        {
            // This menu item will run and then immediately return to the main menu.
            menuClearScreen();
            setHostname();
        }
        else if (MenuChoice == "5")
        {
            // This menu item will run and then immediately return to the main menu.
            menuClearScreen();
            setPw();
        }
        else if (MenuChoice == "6")
        {
            // This menu item will run and then immediately return to the main menu.
            menuClearScreen();
            setWiFi();
        }
        else if (MenuChoice == "7")
        {
            // This menu item will run and then immediately return to the main menu.
            menuClearScreen();
            toggleDebug();
        }
        else if (MenuChoice == "0")
        {
            menuExit();
        }
    }
} // END - menuDo()

/*
 * Get characters from Serial Port or timeout if nothing entered.
 */
String menuSerRx(boolean Echo)
{
    unsigned long SessStart = millis();
    const byte numChars = MaxSerRx;
    char receivedChars[numChars]; // an array to store the received data
    boolean newData = false;
    static byte ndx = 0;
    char endMarker1 = '\r'; // Some terminal client apps send a CR
    char endMarker2 = '\n'; // Others just a LF character, therefore we need to check for both
    char rc;
    while (newData == false)
    {
        if (millis() - SessStart > SesTimeout)
        {
            SerSess = false;
            menuClearScreen();
            Serial.print("The menu session has timed out (");
            Serial.print(SesTimeout / 1000);
            Serial.println(" seconds)...");
            menuExit();
            break;
        }
        while (Serial.available())
        {
            SessStart = millis();
            rc = Serial.read();
            if (rc == endMarker1 or rc == endMarker2)
            { // if a CR or LF was received
                // Serial.println("CR or LF detected");
                receivedChars[ndx] = '\0'; // terminate the character array (string)...
                ndx = 0;
                newData = true;
                char temp = Serial.read();
                // goto ReturnReceivedString; // return everything
            }
            else if (rc == 127)
            {                     // A DEL character (decimal 127) was received
                ndx = ndx - 1;    // Set the Array-Pointer back to delete the last character
                Serial.print(rc); // Echo del DEL character back that the Terminal Client app
            }                     // removes the last character from the screen
            else
            {
                receivedChars[ndx] = rc; // Receive normal characters...
                ndx++;
                if (ndx >= numChars)
                {
                    ndx = numChars - 1;
                }

                if (Echo == true)
                { // Normal echo
                    Serial.print(rc);
                }
                else
                { // Hide echo, for example if user types in a password...
                    Serial.print("*");
                }
            }
        }
    }
    return receivedChars;
} // END - menuSerRx()

/*
 * Display the menu
 */
void printMenu()
{
    menuClearScreen();
    Serial.println("- Main Menu -");
    Serial.println("=============");
    Serial.println();
    Serial.println("[1].......Show the Arduino status");
    Serial.println("[2].......Reset Processor");
    Serial.println("[3].......Show temperature & humidity values");
    Serial.println("[4].......Change the Arduino name");
    Serial.println("[5].......Change the Arduino password");
    Serial.println("[6].......Change the Arduino WiFi setup");
    Serial.print("[7].......Toggle Debug - state: [");
    if (DebugNormalOperation == 0)
        Serial.println("OFF]");
    else
        Serial.println("ON]");
    Serial.println();
    Serial.println("[0].......Exit this Menu");
    Serial.println();
    Serial.print("Enter your choice/number: ");

} // END - HC_Menu()

/*
 * Clear terminal screen if supported, else do single println()
 */
void menuClearScreen()
{
    Serial.println();
    // temp commented out as it messes up in the PlatformIO console and I have yet to sort it.
    // Serial.write(0x1B);  // Send - ESC
    // Serial.print("[2J"); // Send - Clear Screen
    // Serial.write(0x1B);  // Send - ESC
    // Serial.print("[H");  // Send - Curser to top left
    // Serial.println(" ");
}

/*
 * Display msg expaining how to go back to main menu and
 * pause until the user does it
 */
void menuGoBack()
{
    Serial.println();
    Serial.println("[0].......go back to Arduino Menu");
    Serial.print("Enter your choice/number: ");
    while (SerSess == true)
    {
        if (menuSerRx(true).length() > 0)
        {
            char temp = Serial.read();
            Serial.println();
            break;
        }
    }
}

/*
 * Display msg expaining how to go back to main Menu or refresh,
 * and pause until the user chooses.
 *
 * Returns
 *      true for Refresh
 *      false for exit
 */
bool menuGoBackOrRefresh()
{
    Serial.println();
    Serial.println("[0].......go back to Arduino Menu");
    Serial.println("[enter]...to refresh");
    Serial.print("Enter your choice/number: ");
    if (menuSerRx(true).length() > 0)
    {
        char temp = Serial.read();
        Serial.println();
        return (false);
    }
    else
    {
        Serial.println();
        Serial.println();
        return (true);
    }
}

/*
 * Exit Menu, resume normal operation
 */
void menuExit()
{
    menuClearScreen();
    Serial.println("Press 'm' to open menu again.");
    Serial.println("loop() operation has resumed...");
    Serial.println();

    SerSess = false; // clear flag that holds us in the menu system.
}

// END - SerSrvMnu_fns.cpp