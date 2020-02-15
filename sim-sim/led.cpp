#include "led.h"
#include <Arduino.h>

using namespace telephone;

Led::Led(int ledPin) {
  pin = ledPin;
  halfPeriod = 0;
  blinkCounter = 0;
  pinMode(pin, OUTPUT);
}

void Led::setOff() {
  halfPeriod = 0;
  digitalWrite(pin, LOW);
}

void Led::setOn() {
  halfPeriod = 0;
  digitalWrite(pin, HIGH);
}

void Led::setBlink(long periodInMillis) {
  setBlink(periodInMillis, -1);
}

void Led::setBlink(long periodInMillis, int count) {
  halfPeriod = periodInMillis / 2;
  startMillis = millis();
  blinkState = HIGH;
  blinkCounter = count;
  digitalWrite(pin, blinkState);
}

void Led::refresh(long millis) {
  if (halfPeriod == 0) return;
  if (millis - startMillis >= halfPeriod) {
    startMillis = millis;
    blinkState = !blinkState;
    digitalWrite(pin, blinkState);
    
    if (blinkCounter > 0) {
      if (!blinkState)
        blinkCounter--;
      if (blinkCounter == 0)
        halfPeriod = 0; // stop blinking 
    }
  }
}
