int medConfig[10][2];

void setup() {
    Serial.begin(9600);
    int i = 0;
  
    while (i < 10) {
	init_dosage(i);
	init_timing(i);
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


void init_dosage(int i) {
    // TODO: modifies medConfig[i][0] through serial TUI
}

void init_timing(int i) {
    // TODO: modifies medConfig[i][1] through serial TUI
}


void alert_visual() {
    // TODO
}

void alert_verbal() {
    // TODO
}

void measure_motion() {
    // TODO
}

void check_motion_threshold() {
    // TODO
}

void move_platform() {
    // TODO
}

void move_arm() {
    // TODO
}

void dispense_medication() {
    // TODO
}

void alert_caregiver() {
    // TODO
}
