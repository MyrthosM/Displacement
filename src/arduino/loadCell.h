#ifndef ardUsonic_h
#define ardUsonic_h

#include "Arduino.h"

#define KG 1
#define LBS 0

class loadCell
{
  public:
  loadCell(int DAT, int CLK);
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
