/// @file    ArrayOfLedArrays.ino
/// @brief   Set up three LED strips, all running from an array of arrays
/// @example ArrayOfLedArrays.ino

// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with, only this time they're going
// to be all parts of an array of arrays.

#include <FastLED.h>

#define NUM_STRIPS 6
#define NUM_LEDS_PER_STRIP 12
  CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  // tell FastLED there's 60 NEOPIXEL leds on pin 2
  FastLED.addLeds<NEOPIXEL, 8>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 9>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 10>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 11>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 12>(leds[4], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, 13>(leds[5], NUM_LEDS_PER_STRIP);
}



void loop() {
  // This outer loop will go over each strip, one at a time
  for (int x = 0; x < NUM_STRIPS; x++) {
    // This inner loop will go over each led in the current strip, one at a time
    for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
      leds[x][i] = CRGB(random(256), random(256), random(256));

      // leds[x][i] = CRGB::Black;
    }
  }
  FastLED.show();
  delay(100);
}
