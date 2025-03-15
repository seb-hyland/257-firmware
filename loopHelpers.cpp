#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "globals.h"

// Configuring the lcd display connected to the breadboard
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initializing a variable to keep track of the light sensor value
int sensorValue = 0;

// Initializing a global to hold the LCD display status
LCDStatus displayStatus;

void checkStatus() {
    for (int i = 0; i < 10; i++) {
	if (globalConfig[i].initialized) {
	    switch (checkTimeMatch(i, time)) {
	    case TRUE:
		// Medicine not yet taken
		if (rtc.getEpoch() - globalConfig[i].lastDose > 30 * 60) {
		    if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
			displayStatus = LCDStatus::ALERT_MEDICATION;
		    }
		    int state = buzzer.getState();
		    if (state == BUZZER_IDLE) {
			buzzer.playMelody();
		    }

		    measureBrightness();
		}
		// Medicine taken
		else if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
		    buzzer.stop();
		}
		break;
	    case FALSE:
		if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
		    buzzer.stop();
		}
		break;
	    case SAME_HOUR:
		// Medicine was missed!
		if (rtc.getEpoch() - globalConfig[i].lastDose > 60 * 60) {
		    displayStatus = LCDStatus::ALERT_CAREGIVER;
		    buzzer.beep();
		}
		break;
	    }
	}
    }
}

enum TimeMatch {
    TRUE,
    FALSE,
    SAME_HOUR,
};

TimeMatch checkTimeMatch(int i) {
    if (globalConfig[i].times == (long) rtc.getHours()) {
	if (rtc.getMinutes() <= 30) {
	    return TimeMatch::TRUE;
	} else {
	    return TimeMatch::SAME_HOUR;
	}
    } else {
	return TimeMatch::FALSE;
    }
}

enum LCDStatus {
    ALERT_MEDICATION,
    ALERT_CAREGIVER,
    OFF
};

void lcdManager() {
    switch (displayStatus) {
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
