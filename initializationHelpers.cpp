#include<Arduino.h>
#include <StandardCplusplus.h>
#include <vector>
#include <array>

// RTC lib: https://github.com/cvmanjoo/RTC/wiki
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
