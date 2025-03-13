#include <StandardCplusplus.h>
#include <vector>
#include <array>

#include "globals.h"

struct timing {
    long frequency;
    vector<long> times;
};

struct MedConfig {
    int dosage;
    timing timing;
    bool initialized;
};

MedConfig globalConfig[10];

//configuring the lcd display connected to the breadboard
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//initializing a variable to keep track of the light sensor value
int sensorValue = 0;

void setup() {
    lcd.begin(16, 2);
    pinMode(A0, INPUT);

    Serial.begin(9600);
    int i = 0;
  
    while (i < 10) {
	globalConfig[i][0] = initDosage(i);
	globalConfig[i][1] = initTiming(i);
	globalConfig[i][2] = true;
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
		globalConfig[j][2] = false;
	    }
	    break;
	}
    }
} 

void loop() {
    unsigned long currentTime = millis();

    // TODO
}
