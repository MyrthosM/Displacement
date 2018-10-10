#define TRIGGER_PIN 13
#define ECHO_PIN 12
#define USONIC_DIV 58.0
#define MEASURE_SAMPLE_DELAY 5
#define MEASURE_SAMPLES 25
#define MEASURE_DELAY 250

void setup()
{
	// Serial monitoring
	Serial.begin(115200);
	
	// Initializing Trigger Output and Echo Input
	pinMode(TRIGGER_PIN, OUTPUT);
	pinMode(ECHO_PIN, INPUT);
	
	// Reset the trigger pin and wait a half a second
	digitalWrite(TRIGGER_PIN, LOW);
	delayMicroseconds(500);
}

long singleMeasurement()
{
	long duration = 0;
	
    if(TRIGGER_PIN) {
		//Ensure trigger pin was LOW before measurement.
		digitalWrite(TRIGGER_PIN, LOW);
		//Wait 2us
		delayMicroseconds(2);
	}
	// Measure: Set Trigger High to begin measurement.
	digitalWrite(TRIGGER_PIN, HIGH);
	// wait for 11 µs
	delayMicroseconds(11);
	// put the trigger down
	digitalWrite(TRIGGER_PIN, LOW);
	//  and wait for the echo
	duration = pulseIn(ECHO_PIN, HIGH);
	return (long) (((float) duration / USONIC_DIV) * 10.0);
}

long measure()
{
	long measureSum = 0;
	for (int i = 0; i < MEASURE_SAMPLES; i++)
	{
		delay(MEASURE_SAMPLE_DELAY);
		measureSum += singleMeasurement();
	}
	return measureSum / MEASURE_SAMPLES;
}

void loop()
{
	delay(MEASURE_DELAY);
	long distance = measure();
	Serial.print("Distance: ");
	Serial.print(distance);
	Serial.println(" mm");
}