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

array<int, 2> initTime() {
    array<int, 2> curTime;

    Serial.println("Enter the current hour in 24-hour time.");
    Serial.println("Ex: If it is 4:32 pm, enter `16`.");
    while (true) {
	if (Serial.available() > 0) {
	    String input = serial.readString();
	    long intInput = input.parseInt();

	    if (input != '0' && intInput == 0) {
		Serial.println("Invalid input. Please try again, entering a single nonzero number:");
	    } else if (intInput >= 0 && intInput < 24) {
		Serial.println("Invalid input. Please try again, entering a number between 0 and 23:");
	    } else {
		curTime[0] = intInput;
		break;
	    }
	}
    }

    Serial.println("Enter the current minute.");
    Serial.println("Ex: If it is 4:32 pm, enter `32`.");
    while (true) {
	if (Serial.available() > 0) {
	    String input = serial.readString();
	    long intInput = input.parseInt();

	    if (input != '0' && intInput == 0) {
		Serial.println("Invalid input. Please try again, entering a single nonzero number:");
	    } else if (intInput >= 0 && intInput < 60) {
		Serial.println("Invalid input. Please try again, entering a number between 0 and 59:");
	    } else {
		curTime[1] = intInput;
		break;
	    }
	}
    }

    return curTime;
}


int initDosage() {
    Serial.println("Enter the dosage required for this medication.");
    Serial.println("Ex: If two pills should be taken at a time, enter `2`.");
    while (true) {
	if (Serial.available() > 0) {
	    long input = serial.parseInt();

	    if (input > 0) {
		return input;
	    }
	}
	Serial.println("Invalid input. Please try again, entering a single nonzero number:");
    }
}

timing initTiming() {
    timing result;
    
    Serial.println("Enter the frequency (in days) at which this medication should be taken.");
    Serial.println("Ex: If the medication should be taken daily, enter `1`. If it should be taken every other day, enter `2`.");
    while (true) {
	if (Serial.available() > 0) {
	    long input = serial.parseInt();

	    if (input > 0) {
		result[0] = input;
		break;
	    }
	}
	Serial.println("Invalid input. Please try again, entering a single nonzero number:");
    }

    Serial.println("Enter the time(s) of day at which this medication should be taken as a comma-separated list.");
    Serial.println("Ex: For a medication that needs to be taken at 9am and 6pm, enter `9,18`");
    while (true) {
	if (Serial.available() > 0) {
	    parsedInput = readCSV();
	    if (!parsedInput.empty()) {
		result[1] = parsedInput;
		break;
	    }
	    Serial.println("Invalid input. Please try again, entering a comma-separated list of numbers.");
	}
    }

    return result;
}

vector<long> readCSV() {
    String input = Serial.readString();
    input.trim();
    
    int idx = 0;
    vector<long> result;

    while (true) {
	int nextCommaIdx = input.indexOf(',', idx);

	String substring;
	// Last comma
	if (nextCommaIdx == -1) {
	    substring = input.substring(idx);
	} else {
	    substring = input.substring(idx, nextCommaIdx);
	}

	long parsedInt = substring.toInt();
	// Represents invalid substring
	if (substring != '0' && parsedInt == 0) {
	    return vector<long>();
	}
	result.push_back(parsedInt);

	idx = nextCommaIdx + 1;
	if (nextCommaIdx == -1) {
	    break;
	}
    }
}


void alertVisual() {
    // TODO
}

void alertVerbal() {
    // TODO
}

void measureMotion() {
    // TODO
}

void checkMotionThreshold() {
    // TODO
}

void movePlatform() {
    // TODO
}

void moveArm() {
    // TODO
}

void dispenseMedication() {
    // TODO
}

void alertCaregiver() {
    // TODO
}
