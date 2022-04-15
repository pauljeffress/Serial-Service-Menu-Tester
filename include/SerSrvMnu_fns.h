/*
 * SerSrvMnu.h
 * 
 */

#ifndef SERSRVMNU_FNS_H
#define SERSRVMNU_FNS_H

#include <Arduino.h>

/* defines */

/* define any enums */

/* define any struct's */

/* extern global variables */

/* function pre defines */
void menuDo();
String menuSerRx(boolean Echo);
void printMenu();
void menuClearScreen();
void menuGoBack();
bool menuGoBackOrRefresh();
void menuExit();

#endif
// END - misc_fns.h



