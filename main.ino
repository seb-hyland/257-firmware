#include "initializationHelpers.cpp"
#include "loopHelpers.cpp"

#include <StandardCplusplus.h>
#include <vector>
#include <array>


struct timing {
    long frequency;
    vector<long> times;
};

struct MedConfig {
    int dosage;
    timing timing;
    bool isInitialized;
    time lastDispensedTime;
};

MedConfig globalConfig[10];


void setup() {
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
	}
    }
} 

void loop() {
    // time time = getTime();
    // if curHour == 0 set all lastTakens to -1
    // checkStatus(time);
}

