#ifndef gsm_h
#define gsm_h

#include <SoftwareSerial.h>

namespace telephone
{
  class Gsm
  {
    public:
      Gsm(int txPin, int rxPin);
      int checkHandshake();
      int signalQuality();
    private:
      SoftwareSerial* gsmSerial;

      String sendCommand(String command);
  };
}

#endif
