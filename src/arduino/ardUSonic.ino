#include "ardUsonic.h"

ardUsonic sensor(12,13);

void setup()
{
  Serial.begin(9600);
  delay(1000);
}

void loop()
{
  Serial.println(sensor.microsecondsToMillimeters(sensor.Timing(), 23));
  delay(17);
  Serial.print("TIMING");
  Serial.println(sensor.Timing());
  Serial.print("MM");
  Serial.println(sensor.Ranging(MM));
  delay(200);
  Serial.print("TD");
  Serial.println(sensor.TestDistance());
  delay(200);
  Serial.print("CM");
  Serial.println(sensor.Ranging(CM));


}
