
/*
 *  main.cpp
 */ 

#include "global.h"

// my dummy parameter globals
String ArduinoPassword;
String ArduinoHostname;
String ArduinoSSID;
String ArduinoKEY;
int Temp;
int Humi;

// Serial Service Menu globals
const int MaxSerRx = 64;
boolean SerSess = false;          // Serial Session = false upon start
unsigned long SesTimeout = 60000; // Normal operation is resumed after Serial Session timeout

// debugging state globals
boolean DebugNormalOperation = false;
boolean DebugSomthingElse = false;
boolean FlipDebugOnlyOnce = false;