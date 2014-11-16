#include <RFduinoBLE.h>
#include <Adafruit_NeoPixel.h>

#define PIN      6
#define N_LEDS 144

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  strip.begin();
//  strip.setBrightness(1);
  strip.setPixelColor(1, strip.Color(255, 0, 0));
  strip.setPixelColor(2, strip.Color(0, 255, 0));
  strip.setPixelColor(3, strip.Color(0, 0, 255));
  strip.show();
}

void loop() {
//  chase(strip.Color(255, 0, 0)); // Red
//  chase(strip.Color(0, 255, 0)); // Green
//  chase(strip.Color(0, 0, 255)); // Blue
}

static void chase(uint32_t c) {
  for(uint16_t i=0; i<strip.numPixels()+4; i++) {
      strip.setPixelColor(i  , c); // Draw new pixel
      strip.setPixelColor(i-4, 0); // Erase pixel a few steps back
      strip.show();
      delay(25);
  }
}
