
#include "ExpansionDriver.h"
#include "SparkFun_SHTC3.h"
#include <SGBotic_I2CPing.h>
#include "Wire.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SparkFun_VEML7700_Arduino_Library.h>

VEML7700 lightSensor;
SHTC3 mySHTC3;
SGBotic_I2CPing sonar;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 32, &Wire);

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
	setChannel(0);
	while (lightSensor.begin() == false)
	{
		Serial.println("Unable to communicate with the VEML. Please check the wiring. Freezing...");
	}
	setChannel(2);
	while (lightSensor.begin() == false)
	{
		Serial.println("Unable to communicate with the VEML. Please check the wiring. Freezing...");
	}
	setChannel(3);
	errorDecoder(mySHTC3.begin());
	delay(500);
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.display();
}

void ExpansionDriver::displayWrite(String text)
{
	setChannel(3);
	display.clearDisplay();
	display.setRotation(2);
	display.setTextSize(1);
	display.setTextColor(SSD1306_WHITE);
	display.setCursor(0, 0);
	display.print(text);
	display.setCursor(0, 0);
	display.display();
}

void ExpansionDriver::readSensors()
{
	setChannel(0);
	left_light = lightSensor.getLux();
	setChannel(2);
	right_light = lightSensor.getLux();
	
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
