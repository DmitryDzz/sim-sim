#include "beeper.h"
#include <Arduino.h>

using namespace telephone;

Beeper::Beeper(int beeperPin) {
  pin = beeperPin;
  frequency = DEFAULT_FREQUENCY;
  halfPeriod = 0;
  beepCounter = 0;
  pinMode(pin, OUTPUT);
}

void Beeper::setFrequency(int frequency) {
  this->frequency = frequency;
}

int Beeper::getFrequency() {
  return frequency;
}

void Beeper::beep(long durationInMillis) {
  beep(durationInMillis, 1);
}

void Beeper::beep(long periodInMillis, int count) {
  sound(false);
  if (count <= 0) return;
  halfPeriod = periodInMillis / 2;
  startMillis = millis();
  beepState = HIGH;
  beepCounter = count;
  sound(true);
}

void Beeper::stop() {
  halfPeriod = 0;
  sound(false);
}

void Beeper::refresh(long millis) {
  if (halfPeriod == 0) return;
  if (millis - startMillis < halfPeriod) return;

  startMillis = millis;
  beepState = !beepState;
  sound(beepState);

  if (beepCounter > 0) {
    if (!beepState)
      beepCounter--;
    if (beepCounter == 0)
      halfPeriod = 0; // stop
  }
}

void Beeper::sound(bool play) {
  if (play)
    tone(pin, frequency);
  else
    noTone(pin);
}
