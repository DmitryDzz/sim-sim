#ifndef led_h
#define led_h

namespace telephone
{
  class Led
  {
    public:
      Led(int ledPin);
      void setOff();
      void setOn();
      void setBlink(long periodInMillis, int count);
      void setBlink(long periodInMillis);
      void refresh(long millis);
    private:
      int pin;

      bool blinkState;
      int blinkCounter;
      long halfPeriod;
      long startMillis;
  };
}

#endif
