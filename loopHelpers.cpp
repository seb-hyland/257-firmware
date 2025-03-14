#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "globals.h"

#define LED_PIN 6
#define LIGHT_THRESHOLD 4

Servo servo;

// Configuring the lcd display connected to the breadboard
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initializing a variable to keep track of the light sensor value
int sensorValue = 0;

//initializing variable for solenoid
int solenoidPin = 8;

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
            ledManager(LEDStatus::ON);
		    measureBrightness(i);
		}
		// Medicine taken
		else if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
		    buzzer.stop();
		    ledManager(LEDStatus::OFF);
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
		    ledManager(LEDStatus::OFF);
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

enum checkTimeMatch(int i, time_t time) {
    //if they match then switches TimeMatch function
    for(int j = 0; j < globalConfig[i].timing.size(), j++) {
        if(globalConfig[i].timing[j] == (int) rtc.getHours()) {
            if((int) rtc.getMinutes() <= 30) {
                return TimeMatch::TRUE;
            }
            else {
                return TimeMatch::SAME_HOUR;
            }

        }
    }

    return TimeMatch::FALSE;
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

long measureBrightness(int index) {
    pinMode(A0, INPUT);

    sensorValue = analogRead(A0);

    checkBrightnessThreshold(sensorValue, index);

}

void checkBrightnessThreshold(int brightness, int index) {
    if(brightness <= LIGHT_THRESHOLD) {
        dispenseMedication(index);
    }
}

void dispenseMedication(int index) {
    movePlatform(index);
    delay(5000);
    moveArm();
    delay(5000);
    movePlatform(0);

}

void movePlatform(int index) {
    servo.attach(A1);
    if(index == 0) {
    servo.write(0);
    }

    if (index => 4) {
        index = index - 4;
        int location_degrees = 14.3 + (index * 28.6);
    }
    else {
        location_degrees = 329.22 + 14.3 + (index * 28.6);
    }

    servo.write(location_degrees);
}

void moveArm() {
    pinMode(solenoidPin, OUTPUT);

    digitalWrite(solenoidPin, HIGH);      //Switch Solenoid ON
    delay(3000);                          //Wait 1 Second
    digitalWrite(solenoidPin, LOW);       //Switch Solenoid OFF
}

void alertCaregiver() {
    // TODO
}
