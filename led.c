#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 7
#define NUMPIXELS 46
#define BRIGHTNESS 200

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
#define DELAYVAL 50

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  pixels.clear();
  pixels.setBrightness(BRIGHTNESS);
  pixels.begin();
}

void loop() {
  delay(DELAYVAL);
  centurion();
  pixels.show();
}

int step = 1;
int changecolor = 0;

void centurion() {
  if (changecolor % 2 == 0) {
    for(int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0,150,0));
    }
  }
  if (changecolor % 2 == 1) {
    for(int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, pixels.Color(0,250,215));
    }
  }
  if (BRIGHTNESS <= 0 || BRIGHTNESS >= 255) {
    step = -step;
  }
  if (BRIGHTNESS <= 0) {
    changecolor++;
  }
  BRIGHTNESS += step;
  pixels.setBrightness(BRIGHTNESS);
  delay(25);
}
