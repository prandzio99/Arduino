#include <Adafruit_NeoPixel.h>

// NeoPixel object
Adafruit_NeoPixel strip(16, 0, NEO_GRB + NEO_KHZ800);

// color choice variable
int n = 0;

// color variables
uint32_t violet = strip.Color(76, 0, 153);
uint32_t blue = strip.Color(0, 102, 204);
uint32_t cyan = strip.Color(0, 255, 255);
uint32_t green = strip.Color(128, 255, 0);
uint32_t yellow = strip.Color(255, 255, 0);
uint32_t orange = strip.Color(255, 128, 0);
uint32_t red = strip.Color(255, 0, 0);
uint32_t off = strip.Color(0, 0, 0);

// color variable array
uint32_t color[8] = {violet, blue, cyan, green, yellow, orange, red, off};	// tablica kolorów

void setup() {
  strip.begin();	// strip init
  strip.show();		// strip launch
}

void loop() {
  if(n > 7) n = 0;							// if n > 7 then n = 0
  if(n < 7) {								// if n < 7, then:
    for(int i = 0; i < 16; i++) {				// for each diode
      strip.setPixelColor(i, color[n]);			// set color
      strip.show();								// and launch it
      delay(200);								// do 200ms delay
    }
  } else {
    for(int i = 0; i < 16; i++) {			// if n = 7 then:
      strip.setPixelColor(i, color[n]);		// "turn off" all diodes
    }
    strip.show();							// at once
  }
  n++;										// n = n + 1
  delay(2000);								// delay 2s
}