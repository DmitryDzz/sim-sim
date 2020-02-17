#include "gsm.h"
#include <Arduino.h>

using namespace telephone;

Gsm::Gsm(int txPin, int rxPin) {
  Serial.begin(9600);
  gsmSerial = new SoftwareSerial(txPin, rxPin);
  gsmSerial->begin(9600);
}

String Gsm::sendCommand(String command) {
  delay(500);
  gsmSerial->println(command);
  String result = "";
  delay(500);
  while (gsmSerial->available()) {
    char ch = (char) gsmSerial->read();
    if ((ch != '\n') && (ch != '\r'))
      result += ch;
  }
  //result.remove(0, command.length());
  return result;
}

int Gsm::checkHandshake() {
  String response = sendCommand("AT");
  Serial.print("++++ ");
  Serial.println(response);
//  if (sendCommand("AT") != "OK")
//    return -1;
//  return 0;
}

int Gsm::signalQuality() {
  String response = sendCommand("AT+CSQ");
  Serial.print("++++ ");
  Serial.println(response);
}
