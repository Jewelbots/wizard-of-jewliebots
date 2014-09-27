/*
The sketch demonstrates how to do advertise from a Bluetooth Low Energy 4
to the RFduino, then make an LED connected to pin 3 blink. 
 
It is supposed to be used with the Cordova RFDuino Plugin Blink app
*/
 
#include <RFduinoBLE.h>
#include <Adafruit_NeoPixel.h>
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, 2, NEO_GRB + NEO_KHZ800); 

void setup() {
  strip.begin();
  strip.show();
Serial.begin(9600);     
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
   for (int i = 0; i < len; i++) {
    Serial.print(data[i], DEC);
    Serial.print(" ");
    Serial.print(data[i], HEX);
    Serial.print(" ");
    Serial.print(data[i], OCT);
    Serial.print(" ");
    Serial.println(data[i], BIN);
//  Values may not be printable chars
//    Serial.print(" ");
//    Serial.println(data[i]);
  }
  
//turn off if flag is set to off
if(data[0] == 0){

  strip.begin();
  strip.show();
}

//now set the color
if(data[4] == 1){
strip.setPixelColor(0, strip.Color(100,100,0));
}
else if(data[4] == 2){
strip.setPixelColor(0, strip.Color(100, 0,100));
}
else if(data[4] == 3){
strip.setPixelColor(0, strip.Color(100,0,0));
}
else if(data[4] == 4){
strip.setPixelColor(0, strip.Color(100, 0,100));
}
else{
//strip.setPixelColor(0, strip.Color(0,255,0));
}  
 strip.show(); 
}




