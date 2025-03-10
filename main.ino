#include <StandardCplusplus.h>
#include <vector>

struct timing {
    long frequency;
    vector<long> times;
};

struct MedConfig {
    int dosage;
    timing timing;
};

MedConfig globalConfig[10];


void setup() {
    Serial.begin(9600);
    int i = 0;
  
    while (i < 10) {
	globalConfig[i][0] = initDosage(i);
	globalConfig[i][1] = initTiming(i);
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
	    break;
	}
    }
} 

void loop() {
    unsigned long currentTime = millis();

    // TODO
}


int initDosage(int i) {
}

timing initTiming(int i) {
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
	Serial.println("Invalid input. Please try again, entering a single number:")
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
