#include <Arduino.h>
#include <LiquidCrystal.h>
#include <Servo.h>
#include "globals.h"

//defining variables
#define LED_PIN 6
#define LIGHT_THRESHOLD 4
Servo servo;
#define NOTE_C4  262
#define NOTE_G3  196
#define NOTE_A3  220
#define NOTE_B3  247
#define NOTE_C4  262

//creating the melody to play when the pills are dispensed
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

//how long to play each note for
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
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

//Calls other functions to regulate dispensing medication
void checkStatus() {
    //going through each medication initialized
    for (int i = 0; i < 8; i++) {
	    if (globalConfig[i].initialized) {
	        //checking if it is time to take the medication
	        switch (checkTimeMatch(i, rtc.getEpoch())) {
	        case TRUE: //it is time to take the medication and it has not been taken yet
            //turning on medication reminders if the medication hasn't been taken in the last 30 minutes
		    if ((int)rtc.getEpoch() - globalConfig[i].lastDose > 30 * 60) {
		        if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
			        displayStatus = LCDStatus::ALERT_MEDICATION;
		        }

		        alertVerbal(speakerStatus::MELODY);
                ledManager(LEDStatus::ON);
		        measureBrightness(i);
		    }
		    //turning off medication reminders if the medication has been taken in the last 30 minutes
		    else if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
		        alertVerbal(speakerStatus::OFF);
		        ledManager(LEDStatus::OFF);
		        lcdManager(LCDStatus::OFF);
		    }
		    break;

	        case FALSE: //it is not time to take the medication
		    if (displayStatus != LCDStatus::ALERT_CAREGIVER) {
		        //turning off medication reminders
		        alertVerbal(speakerStatus::OFF);
		        ledManager(LEDStatus::OFF);
                lcdManager(LCDStatus::OFF);
		    }
		    break;

	        case SAME_HOUR: //medication should have been taken but hasn't
		    if ((int)rtc.getEpoch() - globalConfig[i].lastDose > 60 * 60) {
		        while(!careGiverOverride(i)) {
		            //alerting the caregiver that the dose has been missed
		            lcdManager(LCDStatus::ALERT_CAREGIVER);
                    alertVerbal(speakerStatus::ALERT);
                	ledManager(LEDStatus::OFF);
		        }

		    }
		    break;
	        }
	    }
    }
}
//used to keep track of the medication dose times and the current time
enum TimeMatch {
    TRUE,
    FALSE,
    SAME_HOUR,
};

<<<<<<< HEAD
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
=======
//Checks if it is dosage time
TimeMatch checkTimeMatch(int i, time_t time) {
    //goes through every time when the medication needs to be taken
    for(int j = 0; j < globalConfig[i].timing.size(); j++) {
        //checks if it is the same hour
        if(globalConfig[i].timing[j] == (int) rtc.getHours()) {
            //checks if it is within 30 minutes of the dosage time
            if((int) rtc.getMinutes() <= 30) {
                return TimeMatch::TRUE;
            }
            else {
                return TimeMatch::SAME_HOUR;
            }

        }
    }
    return TimeMatch::FALSE;
>>>>>>> 2caef1979d7a9755b9c1a3f3f297e97fe8401498
}

//used to regulate the speaker
enum speakerStatus {
    MELODY,
    ALERT,
    OFF
};

//Turns speaker on and off
void alertVerbal(speakerStatus status) {
    //initializes the speaker pin
    pinMode(7, OUTPUT);

    switch(status) {
        case MELODY: //plays the melody to remind them to take the medication
        while(true) {
            for (int i = 0; i < 8; i++) {

                //calculating the note duration in seconds
                int noteDuration = 1000 / noteDurations[i];
                tone(8, melody[i], noteDuration);

                //pausing between notes
                int pauseBetweenNotes = noteDuration * 1.30;
                delay(pauseBetweenNotes);
                // stop the tone playing briefly
                noTone(8);
            }
        }
        break;

        case ALERT: //plays an alert to notify the
        while(true) {
            tone(7, 220, 100);
            delay(200);
        }
        break;

        case OFF: //plays nothing
        break;
    }
}

//used to regulate the LED
enum LEDStatus {
    ON,
    OFF
};

//Turns LED on and off
void ledManager(LEDStatus status) {
    //initializes the LED
    Serial.begin(9600);
    pinMode(6, OUTPUT);

    switch (status) {
        case ON: //turns LED on
        digitalWrite(LED_PIN, HIGH);
        break;

        case OFF: //turns LED off
        digitalWrite(LED_PIN, LOW);
        break;
    }
}

//used to regulate the LCD
enum LCDStatus {
    ALERT_MEDICATION,
    ALERT_CAREGIVER,
    OFF
};

//Turns LCD on and off
void lcdManager(LCDStatus displayStatus) {
    switch (displayStatus) {
        case ALERT_MEDICATION: //displays reminder to take medication
            lcd.begin(16, 2);
            lcd.setCursor(0,0);
            lcd.print("Please take your");
            lcd.setCursor(1,5);
            lcd.print("  medication");
            break;

        case ALERT_CAREGIVER: //displays alert for caregiver
            lcd.begin(16, 2);
            lcd.setCursor(0,0);
            lcd.print("      ALERT");
            lcd.setCursor(1,5);
            lcd.print("  MISSED DOSE");
            break;

        case OFF: //turns off display
            lcd.clear();
            break;
    }
}

//Measures the value from the light sensor
void measureBrightness(int index) {
    //initializes sensor
    pinMode(A0, INPUT);
    Serial.begin(9600);

    //reads the value from the sensor
    sensorValue = analogRead(A0);

    //calls function to compare sensor value to threshold
    checkBrightnessThreshold(sensorValue, index);

}

//Checks if light sensor is detecting hand at dispenser
void checkBrightnessThreshold(int brightness, int index) {
    //calls function that dispenses medication if the user's hand is there
    if(brightness <= LIGHT_THRESHOLD) {
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

//Moves the medication cartridge to the dispenser site
void movePlatform(int index) {
    //initializing the servo
    servo.attach(A1);
    //returning servo to original position
    if(index == -1) {
        servo.write(0);
    }

    //if the medication is on right half, calculates the location of the cartridge
    if (index >= 4) {
        index = index - 4;
        int location_degrees = 14.3 + (index * 28.6);
    }
    //if the medication is on left half, calculates the location of the cartridge
    else {
        location_degrees = 329.22 + 14.3 + (index * 28.6);
    }
    //moves the cartridge to the front of the device
    servo.write(location_degrees);
}

//Pushes the medication out
void moveArm() {
    //initializes the solenoid arm
    pinMode(solenoidPin, OUTPUT);

    //moves arm forwards to push out medication
    digitalWrite(solenoidPin, HIGH);
    delay(3000);
    //moves arm back to original location
    digitalWrite(solenoidPin, LOW);

//Lets the caregiver turn off missed dose alerts
bool careGiverOverride (int i) {
    //initializes the light sensor
    pinMode(A0, INPUT);
    Serial.begin(9600);

    //checks if the caregiver's hand is there
    if(analogRead(A0) <= LIGHT_THRESHOLD) {
        //turns off alerts and dispenses medication if it is
        alertVerbal(speakerStatus::OFF);
        ledManager(LEDStatus::OFF);
        lcdManager(LCDStatus::OFF);
        dispenseMedication(i);
        //updates the time the last dose was taken at
        globalConfig[i].lastDose = rtc.getEpoch;

        return true;
    }
    return false;
}

