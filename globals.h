#ifndef GLOBALS_H
#define GLOBALS_H

#include <RTC.h>
#include <LiquidCrystal.h>
#include <Servo.h>


//array structure that stores information on each cartridge
extern MedConfig globalConfig[8];
//clock
extern RTC_DS1307 rtc;
//LCD display status tracker
extern LCDStatus displayStatus;
//buzzer
extern ezBuzzer buzzer;
//light sensor
extern int sensorValue;
//LCD
extern LiquidCrystal lcd;

//used to keep track of the medication dose times and the current time
enum TimeMatch {
    TRUE,
    FALSE,
    SAME_HOUR
};

//used to regulate the speaker
enum speakerStatus {
    MELODY,
    ALERT,
    OFF
};

//used to regulate the LED
enum LEDStatus {
    ON,
    OFF
};

//used to regulate the LCD
enum LCDStatus {
    ALERT_MEDICATION,
    ALERT_CAREGIVER,
    OFF
};

//Calls other functions to regulate dispensing medication
void checkStatus();
//Checks if it is dosage time
TimeMatch checkTimeMatch(int i, time_t time);
//Turns speaker on and off
void alertVerbal(speakerStatus status);
//Turns LED on and off
void ledManager(LEDStatus status);
//Turns LCD on and off
void lcdManager(LCDStatus status);
//Measures the value from the light sensor
long measureBrightness(int index);
//Checks if light sensor is detecting hand at dispenser
void checkBrightnessThreshold(int brightness, int index);
//Calls other functions to dispense the medication
void dispenseMedication(int index);
//Moves the medication cartridge to the dispenser site
void movePlatform(int index);
//Pushes the medication out
void moveArm();
//Lets the caregiver turn off missed dose alerts
void careGiverOverride();

#endif
