#include <RFduinoBLE.h>
#include <Adafruit_NeoPixel.h>

//LEDs 
#define PIN 2
#define nLEDS 5
Adafruit_NeoPixel strip = Adafruit_NeoPixel(nLEDS, PIN, NEO_GRB + NEO_KHZ800);

//variables for color
int selectedLED;
int red = 255;
int green = 0; 
int blue = 0;
int brightness = 100;



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
  selectedLED = nLEDS;
}

void loop(){
  checkButton();
  Serial.println("working");
  
  if(clickMode == 0){
    off(selectedLED);
  }
  
  else if(clickMode == 1){
    on(red, green,blue, selectedLED);
  }

  else if(clickMode == 2){
    blinkFast(red, green, blue, selectedLED);

  }

  else if(clickMode == 3){
    blinkSlow(red, green, blue, selectedLED);

  }  
  else if(clickMode == 4){
     loopThroughLeds(red, green, blue);
  }
}

void on(int r, int g, int b, int led){
  tintPixels(r, g, b, brightness, led);  
}

void off(int led){
  tintPixels(255, 255, 255, 0, led);
}

void loopThroughLeds(int r, int g, int b){ 
  if(counter > 50) {
    counter = 0;
    off(nLEDS);  
    LEDindex++;
  }

  if(LEDindex > 4){
    LEDindex = 0;
  }
  tintPixels(r, g, b, 100, LEDindex);  
  counter++; 
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
  alpha = brightness/2+(brightness/2+1)*cos(2*PI/periode*speed);
  if(alpha <= 0)alpha = 1;
  strip.setBrightness(alpha);
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

//function to change led colors, individual or all of them
void tintPixels(int r, int g, int b, int a, int led){
  if(led == nLEDS){
       for(uint16_t i=0; i<strip.numPixels(); i++) {
           uint32_t c = strip.Color((a*r/255) , (a*g/255), (a*b/255));
           strip.setPixelColor(i,c);
       }
   }else{
       strip.setPixelColor(led, strip.Color((a*r/255) , (a*g/255), (a*b/255)));
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
      Serial.println(clickMode);
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
    brightness = data[1];
    clickMode = data[2];
    selectedLED = data[3];

    


    //now set the color
    if(data[4] == 0){
      red = 255;
      green = 255;
      blue = 255;
    }
    else if(data[4] == 1){
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

    else if(data[4] == 3){
      red = 0;
      green = 0;
      blue = 255;
    }
    else if(data[4] == 4){
      red = 0;
      green = 255;
      blue = 255;  
    }
    else if(data[4] == 5){
      red = 255;
      green = 255;
      blue = 0;
    }
    else if(data[4] == 6){
      red = 140;
      green = 0;
      blue = 255;  
    }
    else if(data[4] == 7){
      red = 255;
      green = 0;
      blue = 255;  
    }
   
   
   strip.show(); 
  

}






