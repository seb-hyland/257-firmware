#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>

void checkStatus(time time) {
    // loops over every med
    // for each: checkTimeMatch
        // case TRUE
            // deal with lcdManager and alertVerbal
            // if yes: measureBrightness, checkBrightnessThreshold
            // if yes: dispenseMedication
        // case FALSE
            // do nothing
        // case SAME_HOUR
            // if meds not taken then alertCaregiver
            // turn alertVerbal off
            // lcdManager
}

enum timeMatch {
    TRUE,
    FALSE,
    SAME_HOUR,
};

timeMatch checkTimeMatch(int i, time time) {
    // checks if this medication needs to be taken now
    // if: hour == curHour, curMin < 30, lastTaken == curHour
}

enum lcdStatus {
    ALERT_MEDICATION,
    ALERT_CAREGIVER,
    OFF
};

void lcdManager(enum lcdStatus) {
    switch (lcdStatus) {
        case ALERT_MEDICATION:
            lcd.setCursor(0,0);
            lcd.print("Please take your");
            lcd.setCursor(1,5);
            lcd.print("  medication");

        case ALERT_CAREGIVER:
            lcd.setCursor(0,0);
            lcd.print("      ALERT");
            lcd.setCursor(1,5);
            lcd.print("  MISSED DOSE");

        case OFF:
            lcd.clear();
    }
}

void alertVerbal() {
    // TODO
}

long measureBrightness() {
    // TODO
}

void checkBrightnessThreshold(long brightness) {
    // TODO
}

void dispenseMedication() {
    // TODO
}

void movePlatform() {
    // TODO
}

void moveArm() {
    // TODO
}

void alertCaregiver() {
    // TODO
}
