#include <RFduinoBLE.h>
#include "Button.h"

#define BUTTON_PIN 3
#define RED_PIN 1
#define GREEN_PIN 2

Button button(BUTTON_PIN);
// HeartBeat red(RED_PIN);

void setup() {

}

void loop() {
  // red.tick();
  button.tick();

  if (button.shortPress()){
    // something
  }

  if (button.longPress()){
    // something
  }

//  radio.tick();
}


