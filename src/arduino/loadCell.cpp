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
    delayMicroseconds(10);
    digitalWrite(Trig_pin,LOW);
    duration = pulseIn(Echo_pin, HIGH);
    return duration;
}

float ardUsonic::Ranging(int sys)
{
    Timing();
    distance_cm = ((float)duration / 58) * 10.0 ;
    distance_inc = duration / 74 / 2;
    if (sys == 1) 
    {
        return distance_cm;
    }
    else
    return distance_inc;
}

long ardUsonic::TestDistance()
{
    Timing();
    test_distance = (duration * 340)/2;
    return test_distance;
}

float ardUsonic::microsecondsToMillimeters(long microseconds, int temperature) {

 //The above calculations do not take temperature into account.
 //A 10F difference causes a 4.64 m/s difference in sound velocity.
 //long metersPerSecond = 331.5 + (0.6 * (temperature - 32)/1.8);
 long metersPerSecond = 344.02;
 //long metersPerSecond = 320.8334 + (0.333 * temperature);
 //float millimetersPerSecond = metersPerSecond * 1000.0000;
 //float millimetersPerMicroSecond = millimetersPerSecond / 1000000.00000;
 float millimeters = (metersPerSecond * microseconds)/58;
 return millimeters;
}
