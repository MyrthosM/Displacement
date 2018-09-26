#include "ardUsonic.h"
#include "loadCell.h"
//#include "Servo.h"

//ardUsonic sensor(12,13);
loadCell mirusLoadCell(10,11); // parameter "gain" is ommited; the default value 128 is used by the library
    
void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("Setting scale!");
  delay(500);
  mirusLoadCell.set_scale();
  Serial.println("Taring scale!");
  delay(500);
  mirusLoadCell.tare();
  Serial.println("Tared!");
  Serial.println("Timeout for get_units Function:");
    for(int i = 0; i < 6; i++){
      Serial.println("Starting the timer..");
      delay(1000);  
      Serial.print(i);
      Serial.println("...");
    }
  mirusLoadCell.get_units(10);
  Serial.println("Timeout before main loop");
    for(int i = 0; i < 6; i++){
      Serial.println("Starting the timer..");
      delay(1000);  
      Serial.print(i);
      Serial.println("...");
    }
}

void loop()
{
  
  // Serial.println(sensor.microsecondsToMillimeters(sensor.Timing(), 23));
  // delay(17);
  // Serial.print("TIMING");
  // Serial.println(sensor.Timing());
  // Serial.print("MM");
  // Serial.println(sensor.Ranging(MM));
  // delay(200);
  // Serial.print("TD");
  // Serial.println(sensor.TestDistance());
  Serial.print("Load Cell: ");
  Serial.println(mirusLoadCell.read());
  delay(1000);
//   delay(200);
//   Serial.print("CM");
//   Serial.println(sensor.Ranging(CM));
}
