#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 7
#define NUMPIXELS 16
#define BRIGHTNESS 255

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_RGB + NEO_KHZ800);
#define DELAYVAL 50

void setup() {
  #if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
    clock_prescale_set(clock_div_1);
  #endif

  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);

  pixels.clear();
  pixels.setBrightness(BRIGHTNESS);
  pixels.begin();
}
int check = -1;
void loop() {
  delay(DELAYVAL);
  int mode = read();
  if (mode != check) {
    switch(mode) {
      case 1:
        setRed();
      break;
      case 2:
        setGreen();
      break;
      case 3:
        setBlue();
      break;
      case 4:
        setYellow();
      break;
      case 5:
        setPurple();
      break;
      case 6:
        setCyan();
      break;
      default:
        pixels.clear();
    }
    check = mode;
  }
  pixels.show();
}

int read () {
  int pin0 = pinVal(8);
  int pin1 = pinVal(9);
  int pin2 = pinVal(10);

  int val = (4*pin2) + (2*pin1) + (1*pin0);

  return val;
}

int pinVal(int pin) {
  if (digitalRead(pin) == HIGH) {
      return 1;
  } else {
      return 0;
  }
}
//the color combo is BRG not RGB for some reason
void setRed() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,150,0));
  }
}
void setGreen() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,0,150));
  }
}
void setBlue() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150,0,0));
  }
}
void setYellow() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(0,150,150));
  }
}
void setPurple() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150,150,0));
  }
}
void setCyan() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(150,0,150));
  }
}
