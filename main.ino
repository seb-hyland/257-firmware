#include <StandardCplusplus.h>
#include <vector>
#include <array>
#include "globals.h"

struct MedConfig {
    int dosage;
    vector<long> times;
    bool initialized;
    time_t lastDose;
};

MedConfig globalConfig[10];
RTC rtc;

const BUZZER_PIN = 7;


void setup() {
    lcd.begin(16, 2);
    pinMode(A0, INPUT);

    Serial.begin(9600);
    rtc.startClock();
    buzzer = ezBuzzer(BUZZER_PIN);

    int i = 0;
    while (i < 10) {
	globalConfig[i].dosage = initDosage(i);
	globalConfig[i].times = initTiming(i);
	globalConfig[i].initialized = true;
	globalConfig[i].lastDose = 0;
	i++;

	if (i == 9) {
	    break;
	}

	Serial.println("Press a key to continue:");
	Serial.println(" ——————————————————————————————————————————————— ");
	Serial.println("| Key | Description                             |");
	Serial.println("|—————|—————————————————————————————————————————|");
	Serial.println("|  c  | Continue setting up another medication  |");
	Serial.println("|  f  | Finish calibration                      |");
	Serial.println(" ——————————————————————————————————————————————— ");

	char input;
	while (true) {
	    if (Serial.available() > 0) {
		input = Serial.read();
		if (input == 'f' || input == 'c') {
		    break;
		}
	    }
	}
	if (input == 'f') {
	    for (int j = i; j < 10; j++) {
		globalConfig[j].initialized = false;
	    }
	    break;
	}
    }
} 

void loop() {
    unsigned long currentTime = millis();

    // TODO
}
