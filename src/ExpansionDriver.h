#include "Arduino.h"
#include "SharedData.h"

#define MESURE_CYCLE_TIME 0
#define MESURE_DURATION 120

class ExpansionDriver
{
public:
	ExpansionDriver();
	void readSensors();
	void displayWrite(String text);

	unsigned long mesure_time;

	float degC;
	float degF;
	float humidity;

	int distance_left;
	int distance_center;
	int distance_right;
};
