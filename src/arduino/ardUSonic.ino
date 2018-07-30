#include "ardUsonic.h"

ardUsonic sensor(12,13);

void setup()
{
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  Serial.println(sensor.Ranging(CM));
  delay(100);
}
