/*
 * global.h
 *
 * Overall header file for this project
 *
 */

#ifndef GLOBAL_H
#define GLOBAL_H

#include <Arduino.h>
#include <Adafruit_SleepyDog.h> // Needed to restart the Arduino from the Dashboard by the SAMD WatchDog

#include "SerSrvMnu_fns.h"
#include "misc_fns.h"


/*=======================*/
/* define any enums      */
/*=======================*/

/*=======================*/
/* define any struct's   */
/*=======================*/

/*=======================*/
/* extern my global vars */
/*=======================*/
extern String ArduinoPassword;
extern String ArduinoHostname;
extern String ArduinoSSID;
extern String ArduinoKEY;
extern int Temp;
extern int Humi;

extern const int MaxSerRx;
extern boolean SerSess;
extern unsigned long SesTimeout;

extern boolean DebugNormalOperation;
extern boolean DebugSomthingElse;
extern boolean FlipDebugOnlyOnce;


/*============================*/
/* Function Predefines        */
/*============================*/

#endif
