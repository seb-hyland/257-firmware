#ifndef LOOP_HELPERS_H
#define LOOP_HELPERS_H

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include <vector>

#define LED_PIN 6
#define LIGHT_THRESHOLD 4
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247

extern Servo servo;
extern LiquidCrystal lcd;

// Used to represent a comparison between the medication dose times and the current time
enum TimeMatch {
    TRUE,
    FALSE,
    SAME_HOUR
};

// Used to regulate the speaker
enum speakerStatus {
    MELODY,
    ALERT,
    OFF
};

// Used to regulate the LED
enum LEDStatus {
    ON,
    OFF
};

// Used to regulate the LCD
enum LCDStatus {
    ALERT_MEDICATION,
    ALERT_CAREGIVER,
    OFF
};

void checkStatus();
bool medicationTaken(int i);
TimeMatch checkTimeMatch(int i);
bool medicationWindowTracker();
void alertVerbal(speakerStatus status);
void ledManager(LEDStatus status);
void lcdManager(LCDStatus status);
void measureBrightness(int index);
void checkBrightnessThreshold(int brightness, int index);
void dispenseMedication(int index);
void movePlatform(int index);
void moveArm();
void caregiverReset();

#endif
