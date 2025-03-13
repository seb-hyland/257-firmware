#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "globals.h"

#define LED_PIN 6
Servo servo;

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
	    switch (checkTimeMatch(i, rtc.getEpoch())) {
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
            lcdManager(LEDStatus::ON);
		    measureBrightness();
		}
		// Medicine taken
		else if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
		    buzzer.stop();
		    lcdManager(LEDStatus::OFF);
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

TimeMatch checkTimeMatch(int i, time_t time) {

    // checks if this medication needs to be taken now
    // if: hour == curHour, curMin < 30, lastTaken == curHour
}

enum LEDStatus() {
    ON,
    OFF
};

void ledManager(enum LEDStatus) {
    serial.begin(9600);
    pinMode(6, OUTPUT);
    switch (LCDStatus) {
        case ON:
        digitalWrite(LED_PIN, HIGH);

        case OFF:
        digitalWrite(LED_PIN, LOW);
    }
}

enum LCDStatus {
    ALERT_MEDICATION,
    ALERT_CAREGIVER,
    OFF
};

void lcdManager(enum LCDStatus) {
    switch (displayStatus) {
        case ALERT_MEDICATION:
            lcd.begin(16, 2);
            lcd.setCursor(0,0);
            lcd.print("Please take your");
            lcd.setCursor(1,5);
            lcd.print("  medication");

        case ALERT_CAREGIVER:
            lcd.begin(16, 2);
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
