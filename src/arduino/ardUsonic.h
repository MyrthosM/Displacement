#ifndef ardUsonic_h
#define ardUsonic_h

#include "Arduino.h"

#define CM 1
#define INC 0

class ardUsonic
{
  public:
  ardUsonic(int TP, int EP);
  long Timing();
  long Ranging(int sys);

  private:
  int Trig_pin;
  int Echo_pin;
  long duration,distance_cm,distance_inc;

};

#endif
