/*
The sketch demonstrates how to do advertise from a Bluetooth Low Energy 4
to the RFduino, then make an LED connected to pin 3 blink. 
 
It is supposed to be used with the Cordova RFDuino Plugin Blink app
*/
 
#include <RFduinoBLE.h>
#include <Adafruit_NeoPixel.h>

#define PIN 3
void setup() {
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 3, NEO_GRB + NEO_KHZ800); 

  pinMode(0, OUTPUT); // pin0 to + of led (- to ground)
  digitalWrite(0,HIGH);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  // start the BLE stack
  RFduinoBLE.begin();
}
 
void loop() {
  
}

void RFduinoBLE_onDisconnect()
{
  // don't leave the led on if they disconnect

}
 
void RFduinoBLE_onReceive(char *data, int len)
{
//use data[1] as the # of lights  
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 3, NEO_GRB + NEO_KHZ800); 

//use data[2] to figure out how big the strip is
 int strips[data[2]];

 //the first value determines "on" and "off"  
if(data[0] == 3){
   strip.setPixelColor(0, strip.Color(100,100,0));
 strip.show(); 

}


//now set the color
if(data[4] == '5'){
strip.setPixelColor(0, strip.Color(100,100,0));
}
else if(data[4] == '6'){
strip.setPixelColor(0, strip.Color(100, 0,100));
}
else if(data[4] == '7'){
strip.setPixelColor(0, strip.Color(100,100,0));
}
else if(data[4] == '8'){
strip.setPixelColor(0, strip.Color(100, 0,100));
}
else{
strip.setPixelColor(0, strip.Color(0,255,0));
}


}




