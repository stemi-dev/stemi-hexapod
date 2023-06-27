#include "Arduino.h"
#include "SharedData.h"

#define MESURE_CYCLE_TIME 500
#define MESURE_DURATION 120

class ExpansionDriver
{
public:
	ExpansionDriver();
	void readSensors();
	void displayWrite(String text);
	void readLux();
	void readDistance();
	void readSHT();

	unsigned long mesure_time;

	float degC;
	float degF;
	float humidity;

	int distance_left;
	int distance_center;
	int distance_right;

	float left_light;
	float right_light;
	
	int last_distance_read = 0;
};
