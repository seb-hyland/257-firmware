#include <StandardCplusplus.h>
#include <vector>
#include <Wire.h>
#include <RTClib.h>
#include <Servo.h>
#include <LiquidCrystal.h>

Servo servo;

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//holds information on the timing of medication
struct timing {
    long frequency; //how often it is taken in days
    vector<long> times; //time of the day  to be taken
};

//this is data type which holds the dose amount and the timing of when it is taken
struct MedConfig {
    int dosage; //amount of medication
    timing timing; //how often and what time it is taken at
    int location;
};

//Array to store each cartridges medication
MedConfig globalConfig[10];

void setup() {

    //initializes the LCD display
    lcd.begin(16, 2);

   //attaching the servo connected at pin A1
   servoBase.attach(A1);
   //positioning the servo to start
   servoBase.write(0);

    Serial.begin(9600);
    //to track medications
    int i = 0;

    //adds the info for each cartridge of medication
    while (i < 10) {
	globalConfig[i][0] = initDosage(i);
	globalConfig[i][1] = initTiming(i);
	globalConfig[i][2] = initLocation(i);
	i++;

	if (i == 9) {
	    break;
	}
    //user menu
	Serial.println("Press a key to continue:");
	Serial.println(" ——————————————————————————————————————————————— ");
	Serial.println("| Key | Description                             |");
	Serial.println("|—————|—————————————————————————————————————————|");
	Serial.println("|  c  | Continue setting up another medication  |");
	Serial.println("|  f  | Finish calibration                      |");
	Serial.println(" ——————————————————————————————————————————————— ");

	char input;
	while (true) {
	    //retrieving user input from the menu
	    if (Serial.available() > 0) {
		input = Serial.read();
		if (input == 'f' || input == 'c') {
		    break;
		}
	    }
	}
	if (input == 'f') { //finishes the set up
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

//initializes the timing and returns timing obj with info stored
timing initTiming(int i) {
    timing result;
    
    Serial.println("Enter the frequency (in days) at which this medication should be taken.");
    Serial.println("Ex: If the medication should be taken daily, enter `1`. If it should be taken every other day, enter `2`.");
    //retrieves user input about the timing in between doses
    while (true) {
	if (Serial.available() > 0) {
	    long input = serial.parseInt();
        //stores the input in timing if valid
	    if (input > 0) {
		result[0] = input;
		break;
	    }
	}
	Serial.println("Invalid input. Please try again, entering a single number:")
	    }

    Serial.println("Enter the time(s) of day at which this medication should be taken as a comma-separated list.");
    Serial.println("Ex: For a medication that needs to be taken at 9am and 6pm, enter `9,18`");

    //retrieves the time of day that the dose should be taken
    while (true) {
	if (Serial.available() > 0) {
	    parsedInput = readCSV(); //parses as a list
	    if (!parsedInput.empty()) {
		result[1] = parsedInput; //stores the times
		break;
	    }
	    Serial.println("Invalid input. Please try again, entering a comma-separated list of numbers.");
	}
    }
}

int initLocation(int i) {
    Serial.println("Enter which cartridge this medication is being placed in.");
    Serial.println("Ex. If it is placed in the cartridge at the very front of the device, enter 1, if it is placed directly to the right, enter 2.");
    //retrieves user input about what cartridge the medication is in
    int location;

    while (true) {
	if (Serial.available() > 0) {
	    long input = serial.parseInt();
        //stores the input in timing if valid
	    if (input > 0) {
		location = input;
		break;
	    }
	}
	Serial.println("Invalid input. Please try again, entering a single number:")
	    }

    return location;
}

//reads serial input for times of day when the medication should be taken
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
    // I have it set up so it is printing to LCD board, can change easily
    //need to have some sort of calender system to detect if it is the right day to take medication

     lcd.setCursor(0,0);
     lcd.print("Please take your");
     lcd.setCursor(1,5);
     lcd.print("  medication");
}

void alertVerbal() {
    // TODO
}
//once the time hits, then start to measure motion for 30 minutes, if after 30
//minutes nothing was dispensed then alertCaregiver
void measureMotion() {
    // TODO
}

void checkMotionThreshold() {
    // TODO
}

//have to input the index of the medication that is going to be dispensed
void movePlatform(int index) {
    //finds where the medication of that index is on the platform
    int location = globalConfig[index][2];

    //make the ten a variable that depends on the number of medications?
    int location_degrees = (360/10) * (location - 1);

    //positions the right cartridge at the front of the device and dispenses
    servo.write(location_degrees);
    dispenseMedication();
    //waits and then returns to the original position
    delay(5000);
    servo.write(0);
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
