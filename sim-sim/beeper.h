#ifndef beeper_h
#define beeper_h

namespace telephone
{
  class Beeper
  {
    public:
      Beeper(int beeperPin);
      void setFrequency(int frequency);
      int getFrequency();
      void beep(long durationInMillis);
      void beep(long periodInMillis, int count);
      void stop();
      void refresh(long millis);
    private:
      const int DEFAULT_FREQUENCY = 3900;//2100;
    
      int pin;
      int frequency;

      bool beepState;
      int beepCounter;
      long halfPeriod;
      long startMillis;

      void sound(bool play);
  };
}

#endif
