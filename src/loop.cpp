/*
 *  loop()
 */

#include "global.h"

void loop()
{
    menuDo();   // check for and action user menus.
    
    Serial.print(".");  // Print stuff to show we are running...

    // Example of some debug statements
    if (DebugNormalOperation == true)
    {
        Serial.println("loop() - Debug debug debug...");
    }

    // Some more fake actions to execute to show we are running...
    digitalWrite(LED_BUILTIN, HIGH); // Switch the builtin led on
    delay(250);
    digitalWrite(LED_BUILTIN, LOW); // Switch the builtin led off
    delay(500);

} // END - loop()