#ifndef GLOBALS_H
#define GLOBALS_H

#include <RTC.h>
#include <LiquidCrystal.h>
#include <Servo.h>


// Array structure that stores information on each cartridge
extern MedConfig globalConfig[8];
// RTC
extern RTC_DS1307 rtc;
// LCD display status tracker
extern LCDStatus displayStatus;
// Buzzer
extern ezBuzzer buzzer;
// Light sensor
extern int sensorValue;
// LCD
extern LiquidCrystal lcd;

#endif
