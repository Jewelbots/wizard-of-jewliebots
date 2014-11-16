#include <RFduinoBLE.h>

/*
This sketch blinks the RGB LED on the
RFduino RGB LED / Button  Shield.

It calls the subroutine "color_blink"
several times within the main loop. 
*/

// pin 2 on the RGB shield is the red led
int led_red = 2;
// pin 3 on the RGB shield is the green led
int led_grn = 3;
// pin 4 on the RGB shield is the blue led
int led_blu = 4;


void setup() {
  // setup the leds for output
  pinMode(led_red, OUTPUT);
  pinMode(led_grn, OUTPUT);  
  pinMode(led_blu, OUTPUT);
  RFduinoBLE.iBeacon = true;
  RFduinoBLE.begin();

}

void loop() {
   int d1=700;
   int d2=100;
 
  color_blink(100, 0, 0, d1, d2);
  color_blink(0, 100, 0, d1, d2);
  color_blink(0, 0, 100, d1, d2);
  color_blink(50, 50, 50, d1, d2);
  
}

void color_blink(int red, int green, int blue, int delay01, int delay02) {
  
  analogWrite(led_red, red);
  analogWrite(led_grn, green);
  analogWrite(led_blu, blue);
  delay(delay01);
  digitalWrite(led_red, LOW);
  digitalWrite(led_grn, LOW);
  digitalWrite(led_blu, LOW);
  delay(delay02);
 
}


