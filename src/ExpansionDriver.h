#include "Arduino.h"
#include "SharedData.h"


class ExpansionDriver
{
public:
	ExpansionDriver();
	void readSensors();

	float degC;
	float degF;
	float humidity;
};
