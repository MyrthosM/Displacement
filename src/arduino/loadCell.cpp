//-------------------------------------------------------------------------------------
// loadCell_ADC.h
//-------------------------------------------------------------------------------------

#include <Arduino.h>
#include "loadCell.h"

#if ARDUINO_VERSION <= 106
    // "yield" is not implemented as noop in older Arduino Core releases, so let's define it.
    // See also: https://stackoverflow.com/questions/34497758/what-is-the-secret-of-the-arduino-yieldfunction/34498165#34498165
    void yield(void) {};
#endif

loadCell::loadCell(byte dout, byte pd_sck, byte gain) {
	begin(dout, pd_sck, gain);
	LOADCELL_KOEFICIENT = 60000 / 9.5;
	CODE_DIVIDER_RANGE = gain * 16777216;
}

loadCell::loadCell() {
}

loadCell::~loadCell() {
}

void loadCell::begin(byte dout, byte pd_sck, byte gain) {
	PD_SCK = pd_sck;
	DOUT = dout;

	pinMode(PD_SCK, OUTPUT);
	pinMode(DOUT, INPUT);

	set_gain(gain);
}

bool loadCell::is_ready() {
	return digitalRead(DOUT) == LOW;
}

void loadCell::set_gain(byte gain) {
	switch (gain) {
		case 128:		// channel A, gain factor 128
			GAIN = 1;
			break;
		case 64:		// channel A, gain factor 64
			GAIN = 3;
			break;
		case 32:		// channel B, gain factor 32
			GAIN = 2;
			break;
	}

	digitalWrite(PD_SCK, LOW);
	read();
}

long loadCell::read() {
	// wait for the chip to become ready
	while (!is_ready()) {
		// Will do nothing on Arduino but prevent resets of ESP8266 (Watchdog Issue)
		yield();
	}

	unsigned long value = 0;
	uint8_t data[3] = { 0 };
	uint8_t filler = 0x00;

	// pulse the clock pin 24 times to read the data
	data[0] = shiftIn(DOUT, PD_SCK, MSBFIRST);
	data[1] = shiftIn(DOUT, PD_SCK, MSBFIRST);
	data[2] = shiftIn(DOUT, PD_SCK, MSBFIRST);

	// set the channel and the gain factor for the next reading using the clock pin
	for (unsigned int i = 0; i < GAIN; i++) {
		digitalWrite(PD_SCK, HIGH);
		digitalWrite(PD_SCK, LOW);
	}

	// Replicate the most significant bit to pad out a 32-bit signed integer
	if (data[0] & 0x80) {
		filler = 0xFF;
	} else {
		filler = 0x00;
	}

	// Construct a 32-bit signed integer
	value = ( static_cast<unsigned long>(filler) << 24
			| static_cast<unsigned long>(data[0]) << 16
			| static_cast<unsigned long>(data[1]) << 8
			| static_cast<unsigned long>(data[2]) );

	return static_cast<long>(value);
}

long loadCell::read_average(byte times) {
	long sum = 0;
	for (byte i = 0; i < times; i++) {
		sum += read();
		yield();
	}
	return sum / times;
}

double loadCell::get_value(byte times) {
	return read_average(times) - OFFSET;
}

float loadCell::get_unitsKG(byte times) {

	long dataOUT = get_value(times);
	float value = (dataOUT / CODE_DIVIDER_RANGE)*LOADCELL_KOEFICIENT;

	return value;
}

float loadCell::get_units(byte times) {
	return get_value(times) / SCALE;
}

void loadCell::tare(byte times) {
	double sum = read_average(times);
	set_offset(sum);
}

void loadCell::set_scale(float scale) {
	SCALE = scale;
}

float loadCell::get_scale() {
	return SCALE;
}

void loadCell::set_offset(long offset) {
	OFFSET = offset;
}

long loadCell::get_offset() {
	return OFFSET;
}

void loadCell::power_down() {
	digitalWrite(PD_SCK, LOW);
	digitalWrite(PD_SCK, HIGH);
}

void loadCell::power_up() {
	digitalWrite(PD_SCK, LOW);
}

void loadCell::setupArd(){
  Serial.begin(9600);
  delay(1000);
  Serial.println("Setting scale!");
  delay(500);
  this -> set_scale(312.5);
  Serial.println("Taring scale!");
  delay(500);
  this -> tare();
  Serial.println("Tared!");
  Serial.println("Timeout for get_units Function:");
    for(int i = 0; i < 3; i++){
      Serial.println("Starting the timer..");
      delay(1000);  
      Serial.print(i);
      Serial.println("...");
    }
  Serial.println(this->get_units(10));
  Serial.println("Setup Done.");
  Serial.println("Timeout before main loop");
    for(int i = 0; i < 6; i++){
      Serial.println("Starting the timer..");
      delay(1000);  
      Serial.print(i);
      Serial.println("...");
    }
}
