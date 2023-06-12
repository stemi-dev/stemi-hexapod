
#include "ExpansionDriver.h"
#include "SparkFun_SHTC3.h"
#include <SGBotic_I2CPing.h>
#include "SSD1306Wire.h"
#include "Wire.h"

SHTC3 mySHTC3;
SGBotic_I2CPing sonar;

void setChannel(int channel)
{
	digitalWrite(PIN_A, bitRead(channel, 0));
	digitalWrite(PIN_B, bitRead(channel, 1));
	digitalWrite(PIN_C, bitRead(channel, 2));
}

void errorDecoder(SHTC3_Status_TypeDef message)
{
	switch (message)
	{
	case SHTC3_Status_Nominal:
		Serial.print("Nominal");
		break;
	case SHTC3_Status_Error:
		Serial.print("Error");
		break;
	case SHTC3_Status_CRC_Fail:
		Serial.print("CRC Fail");
		break;
	default:
		Serial.print("Unknown return code");
		break;
	}
}

ExpansionDriver::ExpansionDriver()
{
	pinMode(25, OUTPUT);
	digitalWrite(25, LOW);
	setChannel(3);
	errorDecoder(mySHTC3.begin());
	delay(500);
	oled.init();		   // Initialze SSD1306 OLED display
	oled.clearDisplay();   // Clear screen
	oled.setTextXY(0, 0);  // Set cursor position, start of line 0
	oled.putString("Test 123");
}

void ExpansionDriver::readSensors()
{

	setChannel(3);
	oled.init();		   // Initialze SSD1306 OLED display
	oled.clearDisplay();   // Clear screen
	oled.setTextXY(0, 0);  // Set cursor position, start of line 0
	oled.putString("Test 123");
	delay(100);
	return;
	unsigned int current_time = millis();
	if (current_time - mesure_time > MESURE_CYCLE_TIME)
	{
		for (int i = 0; i < 3; i++)
		{
			setChannel(i);
			sonar.start_measure();
		}
		mesure_time = millis();
	}
	if (current_time - mesure_time > (MESURE_CYCLE_TIME + MESURE_DURATION))
	{
		for (int i = 0; i < 3; i++)
		{
			setChannel(i);
			int val = sonar.get_mesure();
			if (val >= 0)
			{

				if (i == 0)
				{
					distance_left = val;
				}
				else if (i == 1)
				{
					distance_center = val;
				}
				else
				{
					distance_right = val;
				}
			}
		}
	}

	setChannel(3);
	SHTC3_Status_TypeDef result = mySHTC3.update();
	if (mySHTC3.lastStatus == SHTC3_Status_Nominal)
	{
		humidity = mySHTC3.toPercent();
		degC = mySHTC3.toDegC();
		degF = mySHTC3.toDegF();
	}
}
