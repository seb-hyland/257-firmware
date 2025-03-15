#include "loopHelpers.h"
#include "globals.h"

// Creating the melody to play when the pills are dispensed
int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// How long to play each note for (in millis)
int noteDurations[] = {
    250, 125, 125, 250, 250, 250, 250, 250
};

// Configuring the lcd display connected to the breadboard
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

// Initializing a variable to keep track of the light sensor value
int sensorValue = 0;

//initializing variable for solenoid
int solenoidPin = 8;

//Initializing a global to hold the LCD display status
LCDStatus displayStatus;

// Calls other functions to regulate dispensing medication
void checkStatus() {
    // Checks if the caregiver reset should be executed
    caregiverReset();
    for (int i = 0; i < 8; i++) {
        if (globalConfig[i].initialized) {
            // Compare medication time to current RTC
            switch (checkTimeMatch(i)) {
                // Within 30 mins from desired medication time
                case TRUE:
                    // Medicine not yet taken
                    if (!medicationTaken()) {
                        if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
                            displayStatus = LCDStatus::ALERT_MEDICATION;
                        }
                        alertVerbal(speakerStatus::MELODY);
                        ledManager(LEDStatus::ON);
                        measureBrightness(i);
                    }
                    // Medicine taken
                    else if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
                        alertVerbal(speakerStatus::OFF);
                        ledManager(LEDStatus::OFF);
                        lcdManager(LCDStatus::OFF);
                    }
                    break;

                // It is not time to take the medication
	        case FALSE:
	            if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
                        alertVerbal(speakerStatus::OFF);
                        ledManager(LEDStatus::OFF);
                        lcdManager(LCDStatus::OFF);
	            }
	            break;

                // The medication should have been taken by now
	        case SAME_HOUR:
	            // Medicine was missed!
	            if (rtc.getEpoch() - globalConfig[i].lastDose > 60 * 60) {
                        lcdManager(LCDStatus::ALERT_CAREGIVER);
                        alertVerbal(speakerStatus::ALERT);
                        ledManager(LEDStatus::OFF);
	            }
	            break;
            }
	}
    }
}

// Check if the medication i has already been taken within the last 30 minutes
bool medicationTaken(int i) {
    return rtc.getEpoch() - globalConfig[i].lastDose > 30 * 60;
}

// Check medication times against RTC
TimeMatch checkTimeMatch(int i) {
    for (int j = 0; j < globalConfig[i].timing.size(); j++) {
	// Checks if it is the same hour
	if (globalConfig[i].timing[j] == (long) rtc.getHours()) {
	    if (medicationWindowTracker) {
		return TimeMatch::TRUE;
	    }
	    else {
		return TimeMatch::SAME_HOUR;
	    }
	}
    }
    return TimeMatch::FALSE;
}


// Check if medication window has passed 
bool medicationWindowTracker {
    return rtc.getMinutes() < 30;
}


// Turns speaker on and off
void alertVerbal(speakerStatus status) {
    // Initializes the speaker pin
    pinMode(7, OUTPUT);

    switch(status) {
        // Plays a melody to remind user to take the medication
        case MELODY:
            int state = buzzer.getState();
            if (state == BUZZER_IDLE) {
                buzzer.playMelody(melody, noteDurations, 8);
            }
            break;

        // Plays an alert to notify the caretaker
        case ALERT:
            buzzer.beep();
            break;

        // Plays nothing
        case OFF:
            buzzer.stop();
            break;
    }
}

// Turns LED on and off
void ledManager(LEDStatus status) {
    // Initializes the LED
    pinMode(LED_PIN, OUTPUT);

    switch (status) {
        case ON: //turns LED on
            digitalWrite(LED_PIN, HIGH);
            break;

        case OFF: //turns LED off
            digitalWrite(LED_PIN, LOW);
            break;
    }
}

// Manages LCD display 
void lcdManager(LCDStatus status) {
    displayStatus = status;
    switch (status) {
        // Displays reminder to take medication
        case ALERT_MEDICATION:
            lcd.begin(16, 2);
            lcd.setCursor(0,0);
            lcd.print("Please take your");
            lcd.setCursor(1,5);
            lcd.print("  medication");
            break;

        // Displays alert for caregiver
        case ALERT_CAREGIVER:
            lcd.begin(16, 2);
            lcd.setCursor(0,0);
            lcd.print("      ALERT");
            lcd.setCursor(1,5);
            lcd.print("  MISSED DOSE");
            break;

        // Turns off display
        case OFF:
            lcd.clear();
            break;
    }
}

// Measures the value from the light sensor
void measureBrightness(int index) {
    // Initializes sensor
    pinMode(A0, INPUT);

    // Reads the value from the sensor
    sensorValue = analogRead(A0);

    // Calls function to compare sensor value to threshold
    checkBrightnessThreshold(sensorValue, index);
}

// Checks if light sensor is detecting hand at dispenser
void checkBrightnessThreshold(int brightness, int index) {
    // Calls function that dispenses medication if the user's hand is there
    if (brightness <= LIGHT_THRESHOLD) {
        dispenseMedication(index);
    }
}
//Calls other functions to dispense the medication
void dispenseMedication(int index) {
    //moving cartridge to dispensing site
    movePlatform(index);
    delay(5000);
    //using arm to push out medication
    moveArm();
    delay(5000);
    //returning platform to original location
    movePlatform(-1);

    //updating the last dose time
    globalConfig[index].lastDose = rtc.getEpoch();
}

// Moves the medication cartridge to the dispenser site
void movePlatform(int index) {
    // Initializing the servo
    servo.attach(A1);
    // Returning servo to original position
    if (index == -1) {
        servo.write(0);
    }

    int location_degrees;
    // If the medication is on right half, calculates the location of the cartridge
    if (index >= 4) {
        index = index - 4;
        location_degrees = 14.3 + (index * 28.6);
    }
    // If the medication is on left half, calculates the location of the cartridge
    else {
        location_degrees = 329.22 + 14.3 + (index * 28.6);
    }
    // Moves the cartridge to the front of the device
    servo.write(location_degrees);
}

// Pushes the medication out
void moveArm() {
    // Initializes the solenoid arm
    pinMode(solenoidPin, OUTPUT);

    // Moves arm forwards to push out medication
    digitalWrite(solenoidPin, HIGH);
    delay(3000);

    // Moves arm back to original location
    digitalWrite(solenoidPin, LOW);
}

// Lets the caregiver turn off missed dose alerts
void caregiverReset () {
    // Initializes the light sensor
    pinMode(A0, INPUT);
    Serial.begin(9600);

    // Checks if the caregiver's hand is present 
    if (analogRead(A0) <= LIGHT_THRESHOLD) {
        // Turns off alerts and dispenses medication if it is
        alertVerbal(speakerStatus::OFF);
        ledManager(LEDStatus::OFF);
        lcdManager(LCDStatus::OFF);
        dispenseMedication(i);

        // Updates the time the last dose was taken for each medication
        // Prevents re-triggering of the caregiver alert
        for (int i = 0; i < 8; i++) {
            globalConfig[i].lastDose = rtc.getEpoch();
        }
    }
}
