
#include "ExpansionDriver.h"
//#include "SparkFun_SHTC3.h"
#include "Wire.h"


//SHTC3 mySHTC3;

void setChannel(int channel)
{
	digitalWrite(PIN_A, bitRead(channel, 0));
	digitalWrite(PIN_B, bitRead(channel, 1));
	digitalWrite(PIN_C, bitRead(channel, 2));
}
/*
void errorDecoder(SHTC3_Status_TypeDef message) // The errorDecoder function prints "SHTC3_Status_TypeDef" resultsin a human-friendly way
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
}*/

ExpansionDriver::ExpansionDriver()
{
	pinMode(25, OUTPUT);
	digitalWrite(25, LOW);
	setChannel(3);
	delay(1);

	//errorDecoder(mySHTC3.begin());
}

void ExpansionDriver::readSensors()
{
	/*
	setChannel(3);
	delay(1);
	SHTC3_Status_TypeDef result = mySHTC3.update();
	if (mySHTC3.lastStatus == SHTC3_Status_Nominal) // You can also assess the status of the last command by checking the ".lastStatus" member of the object
	{
		humidity = mySHTC3.toPercent();
		degC = mySHTC3.toDegC();
		degF = mySHTC3.toDegF();
	}*/
}
