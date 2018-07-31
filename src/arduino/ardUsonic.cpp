#include "Arduino.h"
#include "ardUsonic.h"

ardUsonic::ardUsonic(int TP,int EP)
{
    pinMode(TP,OUTPUT);
    pinMode(EP,INPUT);
    Trig_pin = TP;
    Echo_pin = EP;
}

long ardUsonic::Timing()
{
    digitalWrite(Trig_pin, LOW);
    delayMicroseconds(2);
    digitalWrite(Trig_pin,HIGH);
    delayMicroseconds(4);
    digitalWrite(Trig_pin,LOW);
    duration = pulseIn(Echo_pin, HIGH);
    return duration;
}

long ardUsonic::Ranging(int sys)
{
    Timing();
    distance_cm = duration /29 / 2 ;
    distance_inc = duration / 74 / 2;
    if (sys)
    return distance_cm;
    else
    return distance_inc;
}
