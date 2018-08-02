#ifndef ardUsonic_h
#define ardUsonic_h

#include "Arduino.h"

#define CM 1
#define INC 0
#define MM 2

class ardUsonic
{
  public:
  ardUsonic(int TP, int EP);
  long Timing();
  float Ranging(int sys);
  long TestDistance();
  float microsecondsToMillimeters(long microseconds, int temperature);

  private:
  int Trig_pin;
  int Echo_pin;
  long duration,distance_inc,test_distance;
  float distance_cm, millimeters ,distance_mm;

};

#endif
