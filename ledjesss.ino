#include <FastLED.h>

#define kleurtjespin  2


void setup() {
  FastLED.addLeds<WS2812, kleurtjespin, GRB>(leds, 20);
  
}

void loop() {
  
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  
  
]
  
