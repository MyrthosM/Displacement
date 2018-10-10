#include "ardUsonic.h"
#include "loadCell.h"
//#include "Servo.h"

ardUsonic sensor(12,13);
loadCell mirusLoadCell(A1,A2); // parameter "gain" is ommited; the default value 128 is used by the library
int getUnitsPin = 50;
float calibration_factor = 0.0f;
float getUnitsResult = 0.6;
float getUnitsResultSingle = 0.6;
    
void setup()
{ 
  Serial.begin(38400);
  Serial.println("HX711 Demo");

  Serial.println("Initializing the scale");
  // parameter "gain" is ommited; the default value 128 is used by the library
  // HX711.DOUT	- pin #A1
  // HX711.PD_SCK	- pin #A0
  mirusLoadCell.begin(A1, A2);
  pinMode(getUnitsPin, INPUT_PULLUP);

  // Serial.println("Before setting up the scale:");
  // Serial.print("read: \t\t");
  // Serial.println(mirusLoadCell.read());			// print a raw reading from the ADC

  // Serial.print("read average: \t\t");
  // Serial.println(mirusLoadCell.read_average(20));  	// print the average of 20 readings from the ADC

  // Serial.print("get value: \t\t");
  // Serial.println(mirusLoadCell.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight (not set yet)

  // Serial.print("get units: \t\t");
  // Serial.println(mirusLoadCell.get_units(5), 1);	// print the average of 5 readings from the ADC minus tare weight (not set) divided
	// 					// by the SCALE parameter (not set yet)

  //mirusLoadCell.set_scale(197.8765f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  mirusLoadCell.tare();				        // reset the scale to 0
  mirusLoadCell.set_scale(calibration_factor);                      // this value is obtained by calibrating the scale with known weights; see the README for details

  // Serial.println("After setting up the scale:");

  // Serial.print("read: \t\t");
  // Serial.println(mirusLoadCell.read());                 // print a raw reading from the ADC

  // Serial.print("read average: \t\t");
  // Serial.println(mirusLoadCell.read_average(20));       // print the average of 20 readings from the ADC

  // Serial.print("get value: \t\t");
  // Serial.println(mirusLoadCell.get_value(5));		// print the average of 5 readings from the ADC minus the tare weight, set with tare()

  // Serial.print("get units: \t\t");
  // Serial.println(mirusLoadCell.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
	// 					// by the SCALE parameter set with set_scale

  Serial.println("Readings:");
}

void loop()
{
  if (digitalRead(getUnitsPin) == LOW)
  {
    Serial.println("Getting units");
    getUnitsResultSingle = mirusLoadCell.get_units();
    getUnitsResult = mirusLoadCell.get_units(10);
  }
  Serial.print("one reading:\t");
  Serial.print(getUnitsResultSingle, 5);
  Serial.print("\t| average:\t");
  Serial.println(getUnitsResult, 5);

  mirusLoadCell.power_down();			        // put the ADC in sleep mode
  delay(2000);
  mirusLoadCell.power_up();

  if(Serial.available())
  {
    char temp = Serial.read();
    if(temp == '+' || temp == 'a')
      calibration_factor += 10;
    else if(temp == '-' || temp == 'z')
      calibration_factor -= 10;
    else if(temp == 's')
      calibration_factor += 100;  
    else if(temp == 'x')
      calibration_factor -= 100;  
    else if(temp == 'd')
      calibration_factor += 1000;  
    else if(temp == 'c')
      calibration_factor -= 1000;
    else if(temp == 'f')
      calibration_factor += 10000;  
    else if(temp == 'v')
      calibration_factor -= 10000;  
    else if(temp == 't')
      mirusLoadCell.tare();  //Reset the scale to zero
  }
  // Serial.println(sensor.microsecondsToMillimeters(sensor.Timing(), 23));
  // Serial.print("TIMING");
  // Serial.println(sensor.Timing());
  // Serial.print("MM: ");
  // Serial.print(sensor.Ranging(MM));
  // Serial.print(";");
  // delay(200);
  // Serial.print("TD");
  // Serial.println(sensor.TestDistance());
  // Serial.print("Load Cell: ");
  // Serial.println("15");
  // delay(200);
  // Serial.println(mirusLoadCell.get_units(5),1);
  // delay(1000);
  // delay(200);
  // Serial.print("CM");
  // Serial.println(sensor.Ranging(CM));
}
