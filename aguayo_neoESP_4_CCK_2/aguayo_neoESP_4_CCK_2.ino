/// @file    ArrayOfLedArrays.ino
/// @brief   Set up three LED strips, all running from an array of arrays
/// @example ArrayOfLedArrays.ino

// ArrayOfLedArrays - see https://github.com/FastLED/FastLED/wiki/Multiple-Controller-Examples for more info on
// using multiple controllers.  In this example, we're going to set up three NEOPIXEL strips on three
// different pins, each strip getting its own CRGB array to be played with, only this time they're going
// to be all parts of an array of arrays.

#include <FastLED.h>
#include <limits.h>
#include <algorithm>

// ...


#define NUM_STRIPS 8
#define NUM_LEDS_PER_STRIP 300

CRGB leds[NUM_STRIPS][NUM_LEDS_PER_STRIP];

unsigned long maxLong = ULONG_MAX;
unsigned long t;
CRGB lookupTable[20];
int maxColors = 20;

void generateLookupTableRandom() {
  for (int i = 0; i < 20; i++) {
    lookupTable[i] = CRGB(random(256), random(256), random(256));
  }
  Serial.println("random");
  maxColors = 20;
}

void generateLookupTableAguayo() {
  lookupTable[0] = CRGB(226, 9, 125);
  lookupTable[1] = CRGB(20, 10, 117);
  lookupTable[2] = CRGB(201, 20, 55);
  lookupTable[3] = CRGB(248, 184, 47);
  lookupTable[4] = CRGB(14, 178, 213);
  lookupTable[5] = CRGB(111, 43, 32);
  lookupTable[6] = CRGB(11, 47, 135);
  lookupTable[7] = CRGB(165, 80, 39);
  lookupTable[8] = CRGB(110, 34, 184);
  lookupTable[9] = CRGB(75, 161, 129);
  lookupTable[10] = CRGB(78, 196, 235);
  lookupTable[11] = CRGB(19, 92, 55);
  lookupTable[12] = CRGB(183, 255, 172);
  maxColors = 12;
  Serial.println("aguayo");
}


void generateLookupTableGPT(){
  lookupTable[0] = CRGB(255, 0, 255);
lookupTable[1] = CRGB(0, 255, 255);
lookupTable[2] = CRGB(255, 255, 0);
lookupTable[3] = CRGB(255, 102, 0);
lookupTable[4] = CRGB(255, 0, 0);
lookupTable[5] = CRGB(0, 255, 0);
lookupTable[6] = CRGB(0, 0, 255);
lookupTable[7] = CRGB(204, 0, 204);
lookupTable[8] = CRGB(255, 153, 204);
lookupTable[9] = CRGB(255, 51, 153);
lookupTable[10] = CRGB(255, 204, 51);
lookupTable[11] = CRGB(0, 255, 102);
lookupTable[12] = CRGB(102, 255, 0);
lookupTable[13] = CRGB(0, 204, 255);
lookupTable[14] = CRGB(153, 51, 255);
lookupTable[15] = CRGB(255, 255, 153);
lookupTable[16] = CRGB(255, 102, 255);
lookupTable[17] = CRGB(102, 255, 255);
lookupTable[18] = CRGB(255, 204, 204);
lookupTable[19] = CRGB(102, 255, 102);
lookupTable[20] = CRGB(255, 204, 0);
lookupTable[21] = CRGB(204, 0, 102);
lookupTable[22] = CRGB(0, 153, 255);
lookupTable[23] = CRGB(255, 51, 0);
lookupTable[24] = CRGB(0, 255, 204);
maxColors = 25;
Serial.println("GPT");
}
void generateLookupTable() {
  lookupTable[0] = CRGB(255, 0, 0);
  lookupTable[1] = CRGB(255, 255, 0);
  lookupTable[2] = CRGB(255, 0, 255);
  lookupTable[3] = CRGB(0, 255, 0);
  lookupTable[4] = CRGB(0, 255, 255);
  lookupTable[5] = CRGB(0, 0, 255);
  maxColors = 5;
  Serial.println("8bit");
  // lookupTable[6] = CRGB(11, 47, 135);
  // lookupTable[7] = CRGB(165, 80, 39);
  // lookupTable[8] = CRGB(110, 34, 184);
  // lookupTable[9] = CRGB(75, 161, 129);
  // lookupTable[10] = CRGB(78, 196, 235);
  // lookupTable[11] = CRGB(19, 92, 55);
  // lookupTable[12] = CRGB(183, 255, 172);
}


CRGB pickColor(int index) {
  // int numColors = 6;
  return lookupTable[index % maxColors];
}

CRGB pickRandomColor() {
  return lookupTable[random(maxColors) ];
}

void shuffleLookupTable() {
  std::random_shuffle(std::begin(lookupTable), std::end(lookupTable));
}


// For mirroring strips, all the "special" stuff happens just in setup.  We
// just addLeds multiple times, once for each strip

void setup() {
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

  generateLookupTableGPT();
  Serial.begin(115200);
  FastLED.setBrightness(127);
  randomSeed(analogRead(A0)+analogRead(A0)+analogRead(A0)+analogRead(A0));
   t = random(maxLong);  // Global variable for bytebeat routine
   shuffleLookupTable();
}

uint8_t bytebeatRoutine(int type, int t) {  // uint8_t* buffer,
  uint8_t value;
  switch (type) {
    case 0:
      value = t * (((t >> 12) | (t >> 8)) & (63 & (t >> 4)));
      break;
    case 1:
      value = ((t & 4096) ? ((t * (t ^ t % 255) | (t >> 4)) >> 1) : (t >> 3) | ((t & 8192) ? t << 2 : t));
      break;
    case 2:
      value = t * (t >> 3 | t >> 1) & 255;
      break;
    case 3:
      value = t * (t >> 3 | t >> 9) & 511;
      break;
    case 4:
      value = t * (t >> 3 | t >> 21) & 1023;
      break;
    case 5:
      value = 2 * (t >> 5 & t) - (t >> 5) + t * (t >> 14 & 14);
      break;
    case 6:
      value = (~t >> 2) * ((127 & t * (7 & t >> 10)) < (245 & t * (2 + (5 & t >> 14))));
      break;
    case 7:
      value = t >> 5 | (t << 3) + 12 * t * (t >> 13 | (t >> 1 | t >> 10 | t >> 2) & t >> 8);
      break;
    case 8:
      value = t+(t&t^t>>6)-t*(t>>9&(t%16?2:6)&t>>9);
    break;

    default:
      value = t * (t >> 3 | t >> 21) & 1023;
      break;
  }

  t++;
  return value;
}

int colorIndex = 0;
CRGB temp[NUM_STRIPS];

long period = 30E3;
long periodFormula = 25E3;
long lastChange = 0;
long lastChangeFormula = 0;

int color = 0;

int formula = 0;
void loop() {

  if (millis() > lastChange + period) {

    lastChange = millis();
    shuffleLookupTable();
    
  //   color = (color+1) % 3;
  //   switch (color) {
  //     case 0:
  //       generateLookupTable();
  //       break;
  //     case 1:
  //       generateLookupTableAguayo();
  //       break;
  //     case 2:
  //       generateLookupTableRandom();
  //       break;
  //   }
  }

  if (millis() > lastChange + periodFormula) {
    formula = (formula+1) % 9;
    lastChangeFormula = millis();
  }

  uint8_t bb = bytebeatRoutine(formula, t);
  
  if (random(100) < 4) {
    colorIndex++;
  }

  for (int x = 0; x < NUM_STRIPS; x++) {
    if (bb >> x & 1) {
      temp[x] = pickColor(colorIndex + x);
    } else {
      temp[x] = CRGB(0, 0, 0);
    }
  }
  pushValueToFifo(temp);
  FastLED.show();
  t++;
  delay(33);
}

void pushValueToFifo(CRGB value[]) {
  for (int i = NUM_LEDS_PER_STRIP - 1; i > 0; i--) {
    for (int j = 0; j < NUM_STRIPS; j++) {
      leds[j][i] = leds[j][i - 1];
    }
  }
  for (int i = 0; i < NUM_STRIPS; i++) {
    leds[i][0] = value[i];
  }
}


