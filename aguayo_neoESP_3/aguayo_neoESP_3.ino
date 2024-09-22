/// @file    ArrayOfLedArrays.ino
/// @brief   Set up three LED strips, all running from an array of arrays
/// @example ArrayOfLedArrays.ino

// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with, only this time they're going
// to be all parts of an array of arrays.

#include <FastLED.h>
#include <limits.h>
#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 300

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

unsigned long maxLong = ULONG_MAX;
unsigned long t = random( maxLong);  // Global variable for bytebeat routine
CRGB lookupTable[20];

void generateLookupTable() {
  for (int i = 0; i < 20; i++) {
    lookupTable[i] = CRGB(random(256), random(256), random(256));
  }
}

CRGB pickColor(int index) {
  int numColors = 20;
  return lookupTable[index % numColors];
}


// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip
void setup() {
  // tell FastLED there's 60 NEOPIXEL leds on pin 2
  // FastLED.addLeds<NEOPIXEL, 19>(leds[0], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<NEOPIXEL, 21>(leds[1], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<NEOPIXEL, 18>(leds[2], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<NEOPIXEL, 0>(leds[3], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<NEOPIXEL, 5>(leds[4], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<NEOPIXEL, 4>(leds[5], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<NEOPIXEL, 17>(leds[6], NUM_LEDS_PER_STRIP);
  // FastLED.addLeds<NEOPIXEL, 16>(leds[7], NUM_LEDS_PER_STRIP);

    FastLED.addLeds<NEOPIXEL, D0>(leds[0], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, D1>(leds[1], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, D2>(leds[2], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, D3>(leds[3], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, D4>(leds[4], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, D5>(leds[5], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, D6>(leds[5], NUM_LEDS_PER_STRIP);
  FastLED.addLeds<NEOPIXEL, D7>(leds[5], NUM_LEDS_PER_STRIP);

  generateLookupTable();

}

uint8_t bytebeatRoutine(int type, int t) {  // uint8_t* buffer,
  uint8_t value;
  switch (type) {
    case 0:
      value = t * (((t >> 12) | (t >> 8)) & (63 & (t >> 4)));
      break;
    case 2:
      value = ((t & 4096) ? ((t * (t ^ t % 255) | (t >> 4)) >> 1) : (t >> 3) | ((t & 8192) ? t << 2 : t));
      break;
    case 3:
      value = t * (t >> 3 | t >> 1) & 255;
      break;
    case 4:
      value = t * (t >> 3 | t >> 9) & 511;
      break;
    case 5:
      value = t * (t >> 3 | t >> 21) & 1023;
      break;

    default:
      value = t * (t >> 3 | t >> 21) & 1023;
      break;
  }

  t++;
  return value;
}

int colorIndex = 0;

void loop() {

  


  
  for (int i = 0; i < NUM_LEDS_PER_STRIP; i++) {
    uint8_t bb = bytebeatRoutine(4, t+i);
    if(random(100) < 5) {
      colorIndex++;
    }

    for (int x = 0; x < NUM_STRIPS; x++) {
      // leds[x][i] = CRGB(random(256), random(256), random(256));
      if (bb >> x & 1) {
        leds[x][i] = pickColor(colorIndex+x);
      } else {
        leds[x][i] = CRGB(0, 0, 0);
        
        
      }
    }
  }

  FastLED.show();
  t++;  
  delay(80);
}
