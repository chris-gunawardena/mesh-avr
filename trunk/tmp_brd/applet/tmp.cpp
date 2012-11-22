#include "Arduino.h"
void setup();
void loop();
// read Analog port for 9V Power monitor


#define StatusLed 13
int powerInput = 1;
int sensorValue = 0;
int ledState = HIGH;

void setup() {
	// Define Serial Port
	Serial.begin(57600);
	Serial.println("Starting serial port...");
	delay(2000);

}


void loop() {
	// wait half a second
	delay(500);
	sensorValue = analogRead(powerInput);
	Serial.print("PV = ");
	Serial.println(sensorValue);
	ledState = !ledState;
	digitalWrite(StatusLed, ledState);
	

}
