#include <RFduinoBLE.h>
#include "Button.h"

#define BUTTON_PIN 3
#define RED_PIN 1
#define GREEN_PIN 2

Button button(BUTTON_PIN);
// HeartBeat red(RED_PIN);

void setup() {
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
}

bool red = false;
bool green = false;

void toggleRed(){
  red = !red;
  digitalWrite(RED_PIN, red);
}

void toggleGreen(){
  green = !green;
  digitalWrite(GREEN_PIN, green);
}

void loop() {
  // red.tick();
  button.tick();

  if (button.shortPress()){
    digitalWrite(RED_PIN, HIGH);
  }

  if (button.longPress()){
    digitalWrite(GREEN_PIN, HIGH);
  }

//  radio.tick();
}


