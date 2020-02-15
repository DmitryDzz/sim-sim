#include "button.h"
#include "led.h"
#include "beeper.h"
#include <GSM.h>

using namespace telephone;

const int LED_PIN = 13;
const int CALL_NUMBER_0_PIN = A0;
const int CALL_NUMBER_1_PIN = A1;
const int CALL_NUMBER_2_PIN = A2;
const int CALL_NUMBER_3_PIN = A3;
const int CALL_NUMBER_4_PIN = A4;
const int RING_PIN = A5;

Button btnCallNumber0(0, 1023);
Button btnCallNumber1(0, 1023);
Button btnCallNumber2(0, 1023);
Button btnCallNumber3(0, 1023);
Button btnCallNumber4(0, 1023);

Led led(13);
Beeper beeper(11);

#define SIM_PIN_NUMBER ""
GSM gsmAccess;
GSMVoiceCall gsmVoiceCall;

int freq = 200;

void btnCallNumberHandler(int btnIndex, telephone::ButtonState btnState) {
  if (btnState == PRESSED) {
    if (btnIndex == 0) {
//      freq -= 100;
//      tone(11, freq);
//      delay(200);
//      noTone(11);
//      Serial.print("Freq = ");
//      Serial.println(freq);
      led.setBlink(500, 1);
      beeper.beep(500);
    } else if (btnIndex == 1) {
//      freq += 100;
//      tone(11, freq);
//      delay(200);
//      noTone(11);
//      Serial.print("Freq = ");
//      Serial.println(freq);
      led.setBlink(500, 3);
      beeper.beep(500, 3);
    } else if (btnIndex == 2) {
//      tone(11, freq);
//      delay(200);
//      noTone(11);
//      Serial.print("Freq = ");
//      Serial.println(freq);
      led.setBlink(500);
      beeper.beep(500, 5);
    } else if (btnIndex == 3) {
//      freq = 2100;
//      tone(11, freq);
//      delay(200);
//      noTone(11);
//      Serial.print("Freq = ");
//      Serial.println(freq);
      led.setOn();
      beeper.setFrequency(3900);
      beeper.stop();
    } else if (btnIndex == 4) {
      freq = 3900;
//      tone(11, freq);
//      delay(200);
//      noTone(11);
//      Serial.print("Freq = ");
//      Serial.println(freq);
      led.setOff();
      beeper.setFrequency(2100);
      beeper.stop();
    }
        
    //Serial.print("Pressed ");
  } else {
    //Serial.print("Released ");
  }
  //Serial.println(btnIndex);
}

void btnCallNumberHandler0(telephone::ButtonState btnState) {
  btnCallNumberHandler(0, btnState);
}

void btnCallNumberHandler1(telephone::ButtonState btnState) {
  btnCallNumberHandler(1, btnState);
}

void btnCallNumberHandler2(telephone::ButtonState btnState) {
  btnCallNumberHandler(2, btnState);
}

void btnCallNumberHandler3(telephone::ButtonState btnState) {
  btnCallNumberHandler(3, btnState);
}

void btnCallNumberHandler4(telephone::ButtonState btnState) {
  btnCallNumberHandler(4, btnState);
}

void refreshButtons(long currentMillis) {
  btnCallNumber0.refresh(analogRead(CALL_NUMBER_0_PIN), currentMillis);
  btnCallNumber1.refresh(analogRead(CALL_NUMBER_1_PIN), currentMillis);
  btnCallNumber2.refresh(analogRead(CALL_NUMBER_2_PIN), currentMillis);
  btnCallNumber3.refresh(analogRead(CALL_NUMBER_3_PIN), currentMillis);
  btnCallNumber4.refresh(analogRead(CALL_NUMBER_4_PIN), currentMillis);
}

void debugPrint(String text) {
  Serial.print(text);
}

void debugPrintln(String text) {
  Serial.println(text);
}

void setup()
{
  Serial.begin(9600);
  
  pinMode(CALL_NUMBER_0_PIN, INPUT);
  pinMode(CALL_NUMBER_1_PIN, INPUT);
  pinMode(CALL_NUMBER_2_PIN, INPUT);
  pinMode(CALL_NUMBER_3_PIN, INPUT);
  pinMode(CALL_NUMBER_4_PIN, INPUT);

  btnCallNumber0.setHandler(btnCallNumberHandler0);
  btnCallNumber1.setHandler(btnCallNumberHandler1);
  btnCallNumber2.setHandler(btnCallNumberHandler2);
  btnCallNumber3.setHandler(btnCallNumberHandler3);
  btnCallNumber4.setHandler(btnCallNumberHandler4);

  // No network blinking:
  led.setBlink(250);
  debugPrint("Connecting..");
  while (true) {
    debugPrint(".");
    if (gsmAccess.begin(SIM_PIN_NUMBER) == GSM_READY) {
      debugPrintln("done");
      break;
    }
    delay(1000);
  }
  led.setOff();

  // To be sure that the modem reports on incoming events correctly:
  gsmVoiceCall.hangCall();
}

void loop()
{
  long currentMillis = millis();
  refreshButtons(currentMillis);
  led.refresh(currentMillis);
  beeper.refresh(currentMillis);
}
