#include <RFduinoBLE.h>

int led_red = 1;
int led_grn = 2;
unsigned long lastButtonPress;

void setup() {
  pinMode(led_red, OUTPUT);
  pinMode(led_grn, OUTPUT);  
}

int red(int state = HIGH) {
  digitalWrite(led_red, state);
  return state;
}

int green(int state = HIGH) {
  digitalWrite(led_grn, state);
  return state;
}

unsigned long lastHeartBeat = 0;
int stateHeartBeat = LOW;
void heartBeat(int delay = 200) {
  if (lastHeartBeat < millis() - delay){
    stateHeartBeat = !stateHeartBeat;
    red(stateHeartBeat);
    lastHeartBeat = millis();
  }
}

void loop() {
  heartBeat(200);
}


