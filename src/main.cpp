/*

This file is part of STEMI hexapod library.

Copyright (C) 2017 STEMI d.o.o.
Authors: Luka Fucek, et al.
Contact: info@stemi.education
Web: https://www.stemi.education/

STEMI hexapod library is free software exclusively
for non-commercial activities.

In case of developing any comercial activities involving STEMI
hexapod library please contact stemi.education for providing custom
license at: info@stemi.education.

For non-commercial activities you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License,
or (at your option) any later version.

STEMI hexapod library is
distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with STEMI hexapod library.
If not, see http://www.gnu.org/licenses/.

For additional information please check http://www.stemi.education.

*/

#include "Hexapod.h"
#include <SoftwareSerial.h>
SharedData robot;
Hexapod hexapod;

SoftwareSerial softwareSerial;

bool isMain = false;

void setup()
{
	Serial.begin(9600);
	if (isMain)
	{
		softwareSerial.begin(9600, SWSERIAL_8N1, 25, 15, false);
	}
	else
	{
		softwareSerial.begin(9600, SWSERIAL_8N1, 15, 25, false);
	}
	if (!softwareSerial)
	{ // If the object did not initialize, then its configuration is invalid
		Serial.println("Invalid SoftwareSerial pin configuration, check config");
		while (1)
		{ // Don't continue with invalid configuration
			delay(1000);
		}
	}
	robot.storeName("Mirko");
	hexapod.init();
	robot.setLed(RED);
	robot.setHeight(50);
}

Color clrArray[7] = {BLUE, YELLOW, GREEN, CYAN, PURPLE, RED, ORANGE};
uint8_t clrCount = 0;

void setLEDrandom()
{
	robot.setLedStatic(0, clrArray[random(0, 6)]);
	robot.setLedStatic(1, clrArray[random(0, 6)]);
	robot.setLedStatic(2, clrArray[random(0, 6)]);
	robot.setLedStatic(3, clrArray[random(0, 6)]);
	robot.setLedStatic(4, clrArray[random(0, 6)]);
	robot.setLedStatic(5, clrArray[random(0, 6)]);
}

void setLEDSequence()
{
	robot.setLedStatic(clrArray[clrCount]);
	clrCount = (clrCount + 1) % 7;
}

void loop()
{
	if (isMain)
	{
		softwareSerial.print("#");
		for (int i = 0; i < 10; i++)
		{
			softwareSerial.print(i);
			delay(10);
		}
		softwareSerial.print("#");
	}
	else
	{
		if (softwareSerial.available() > 0)
		{
			String msg = "";
			while (softwareSerial.available() > 0)
			{
				char c = softwareSerial.read();
				msg += c;
			}
			Serial.println(msg);
		}
	}
}