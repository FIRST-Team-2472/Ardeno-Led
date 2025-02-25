#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif
#define PIN 7
#define NUMPIXELS 46
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
        setPattern();
      break;
      case 2:
        setMovingPattern();
      break;
      case 3:
        setRainbow();
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
      case 7:
        
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
void setPattern() {
  for(int i = 0; i < NUMPIXELS; i++) {
    if (i % 9 < 3) {
    pixels.setPixelColor(i, pixels.Color(0,150,0));
    }
    if (i % 9 >= 3 && i % 9 < 6) {
      pixels.setPixelColor(i, pixels.Color(150,0,0));
    }
    if (i % 9 >= 6 &&i % 9 < 9) {
      pixels.setPixelColor(i, pixels.Color(0,0,150));
    }
    if (i % 9 >= 9) {
      pixels.setPixelColor(i, pixels.Color(150,150,150));
    }
  }
  
}
int moving = 1;
void setMovingPattern() {
  for(int i = 0; i < NUMPIXELS; i++) {
    if (i % 2 == moving) {
      pixels.setPixelColor(i, pixels.Color(0,150,0));
    }
    if (i % 2 == abs(moving - 1)) {
      pixels.setPixelColor(i, pixels.Color(150,0,0));
    }
  }
  delay(500);
  moving = abs(moving-1)
}
void setRainbow() {
  for(int i = 0; i < NUMPIXELS; i++) {
    int r = i % 42;
    if (r >= 0 && r < 6){
        pixels.setPixelColor(i, pixels.Color(17,255,0));
    }
    if (r >= 6 && r < 12){
        pixels.setPixelColor(i, pixels.Color(17,255,136));
    }
    if (r >= 12 && r < 18){
        pixels.setPixelColor(i, pixels.Color(0,250,215));
    }
    if (r >= 18 && r < 24){
        pixels.setPixelColor(i, pixels.Color(15,8,200));
    }
    if (r >= 24 && r < 30){
        pixels.setPixelColor(i, pixels.Color(192,8,40));
    }
    if (r >= 30 && r < 36){
        pixels.setPixelColor(i, pixels.Color(225,184,4));
    }
    if (r >= 36 && r < 42){
        pixels.setPixelColor(i, pixels.Color(225,254,57));
    }
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
