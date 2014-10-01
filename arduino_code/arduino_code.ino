#include <RFduinoBLE.h>
#include <Adafruit_NeoPixel.h>

//LEDs 
#define PIN 2
#define nLEDS 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(nLEDS, PIN, NEO_GRB + NEO_KHZ800);

//variables for color
int red = 255;
int green = 0; 
int blue = 0;

//variables for fading
long speed;
int alpha;
int periode = 2000;
int LEDindex = 0;
int counter = 0;

//button
#define BUTTON 4
#define BUTTON_3V 3
int buttonState = 0;
int clickMode = 1;
int shortClick = 600;
//variables for timers
unsigned long buttonStartTime;

//motor
#define MOTOR 1




void setup() {
  strip.begin();
  strip.show(); 
  pinMode(BUTTON, INPUT);
  pinMode(BUTTON_3V, OUTPUT);
  pinMode(MOTOR, OUTPUT);

  Serial.begin(9600);     
  RFduinoBLE.begin();
  

  red = 255;
  blue = 0;
  green = 0;
}

void loop(){
  checkButton();

  if(clickMode == 0){
    Serial.println("mode 0");
     off(nLEDS);
}

  else if(clickMode == 1){
      Serial.println("mode 1");
     on(red, green,blue, nLEDS);
  }

  else if(clickMode == 2){
      Serial.println("mode 2");
 blinkFast(red, green, blue, nLEDS);

  }

  else if(clickMode == 3){
      Serial.println("mode 3");
  blinkSlow(red, green, blue, nLEDS);

  }  
//  else if(clickMode == 4){
//      Serial.println("mode 4");
//  loopThroughLeds(red, green, blue);
//  }
}

void on(int r, int g, int b, int led){
  tintPixels(r, g, b, 100, led);  
}

void off(int led){
  tintPixels(0, 0, 0, 0, led);
}

void loopThroughLeds(int r, int g, int b){
  tintPixels(r, g, b, 100, LEDindex);  
  if(LEDindex == 0) off(nLEDS-1);  
  else off(LEDindex-1);

  counter++; 
  if(counter > 1000) {
    counter = 0;
    LEDindex++;
  }

  if(LEDindex >= 5){
    LEDindex = 0;
  }

}

void blinkFast(int r, int g, int b, int led){
  speed = millis();
  speed *= 2;
  fadePixels(speed, r, g, b, led);
}

void blinkSlow(int r, int g, int b, int led){
  speed = millis();
  speed *= 0.5;
  fadePixels(speed, r, g, b, led);
}

void fadePixels(long speed, int r, int g, int b, int led){
  int previousAlpha = alpha;
  alpha = 128+127*cos(2*PI/periode*speed);
  tintPixels(r, g, b, alpha, led);
}

//function to change led colors, individual or all of them
void tintPixels(int r, int g, int b, int a, int led){
  strip.setBrightness(a);
  if(led == nLEDS){
    for(uint16_t i=0; i<strip.numPixels(); i++) {
      uint32_t c = strip.Color(r, g, b);
      strip.setPixelColor(i,c);
    }
  }
  else{
    strip.setPixelColor(led, strip.Color(r, g, b));
  }
  strip.show();
}



void checkButton(){
  int checkButton = digitalRead(BUTTON);
  unsigned long now = millis();

  if(buttonState == 0){
    if (checkButton == HIGH) {
      buttonState = 1;
      buttonStartTime = now;
      off(nLEDS);
      clickMode++;
      if(clickMode > 4) clickMode = 0; 
    }
  }  
  else if(buttonState == 1){
    if (now > buttonStartTime + shortClick) {
      buttonState = 0;
    }
  }

}


void RFduinoBLE_onDisconnect()
{

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
     red = 255;
     green = 0;
     blue = 0;
  }
  else if(data[4] == 2){
     red = 0;
     green = 255;
     blue = 0;  
   }
  else if(data[4] == 3){
     red = 0;
     green = 0;
     blue = 255;
   }
  else if(data[4] == 4){
    strip.setPixelColor(0, strip.Color(100, 0,100));
  }
  else{
    //strip.setPixelColor(0, strip.Color(0,255,0));
  }  
  strip.show(); 
}





