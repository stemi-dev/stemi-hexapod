#include "Hexapod.h"
#include "Serial.h"
SharedData robot;
Hexapod hexapod;

void setup()
{
	Serial.begin(9600);
	hexapod.init();
	robot.setLed(RED);
	robot.setHeight(50);
}

void loop()
{
	checkSerial();
}
