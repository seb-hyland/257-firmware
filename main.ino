int medConfig[10][2];

void setup() {
  Serial.begin(9600);
  int i = 0;
  
  while ((Serial.available() && Serial.read() != 'f') && i < 10) {
    init_dosage(i);
    init_timing(i);
    i++;
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
