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
#include "ExpansionDriver.h"

SharedData robot;
Hexapod hexapod;

void setup()
{
	Serial.begin(9600);
	hexapod.init(ROBOT_USER_MODE);
	robot.setLed(GREEN);
	robot.setHeight(50);
}

void loop()
{
	if (robot.dataCounter) {
		for (int i = 0; i < robot.dataCounter; i++) {
			String d = robot.data[i];
			if (d.length() < 5) {
				continue;
			}
			Serial.println(d);
			int lb = -1;
			int rb = -1;
			for (int j = 0; j < d.length(); j++) {
				if (d[j] == '(') {
					lb = j;
				} else if (d[j] == ')') {
					rb = j;
				}
			}
			String vars[100];
			String var = "";
			int varBr = 0;
			for (int j = lb + 1; j <= rb; j++) {
				if (d[j] == ' ') {
					continue;
				}
				if (d[j] == ',' || d[j] == ')') {
					vars[varBr] = var;
					Serial.println(var);
					varBr++;
					var = "";
				} else {
					var += d[j];
				}
			}
			if (d.startsWith("robot.move(0, 0, 0)")) {
				Serial.println("robot.stop");
				robot.move(0, 0, 0);
			} else if (d.startsWith("robot.move")) {
				Serial.println("robot.move");
				userPresetInputData var0;
				if (vars[0] == "FORWARD") {
					var0 = FORWARD;
				} else if (vars[0] == "BACKWARD") {
					var0 = BACKWARD;
				} else if (vars[0] == "LEFT") {
					var0 = LEFT;
				} else if (vars[0] == "RIGHT") {
					var0 = RIGHT;
				}
				int var1 = vars[1].toInt();
				robot.move(var0, var1);
			} else if (d.startsWith("delay")) {
				int var0 = vars[0].toInt();
				delay(var0);
			}  else if (d.startsWith("robot.setLed")) {
				Color var0;
				if (vars[0] == "RED") {
					var0 = RED;
				} else if (vars[0] == "BLUE") {
					var0 = BLUE;
				} else if (vars[0] == "GREEN") {
					var0 = GREEN;
				} else if (vars[0] == "YELLOW") {
					var0 = YELLOW;
				} else if (vars[0] == "PURPLE") {
					var0 = PURPLE;
				} else if (vars[0] == "CYAN") {
					var0 = CYAN;
				} else if (vars[0] == "WHITE") {
					var0 = WHITE;
				} else if (vars[0] == "ORANGE") {
					var0 = ORANGE;
				} else if (vars[0] == "BLACK") {
					var0 = BLACK;
				}
				robot.setLed(var0);
			} else if (d.startsWith("robot.rotate")) {
				Serial.println("robot.rotate");
				userPresetInputData var0;
				if (vars[0] == "FORWARD") {
					var0 = FORWARD;
				} else if (vars[0] == "BACKWARD") {
					var0 = BACKWARD;
				} else if (vars[0] == "LEFT") {
					var0 = LEFT;
				} else if (vars[0] == "RIGHT") {
					var0 = RIGHT;
				}
				int var1 = vars[1].toInt();
				robot.rotate(var0, var1);
			}
		}
	}
	robot.dataCounter = 0;
	delay(20);
	return;
	robot.setLedStatic(RED);
	robot.move(FORWARD,2000);
    delay(2000);
	robot.move(FORWARD);
    delay(7000);
    robot.setLedStatic(GREEN);
    delay(500);
    robot.move(RIGHT);
    delay(5000);
    robot.setLedStatic(BLUE);
    delay(500);
    robot.move(BACKWARD);
    delay(7000);
    // STOP
    robot.move(0, 0, 0);
    delay(500);
    robot.setLedStatic(CYAN);
    robot.rotate(LEFT, 10000);
    delay(10000);
    // STOP
    robot.move(0, 0, 0);
    robot.setLedStatic(ORANGE);
    delay(500);
    robot.move(LEFT);
    delay(5000);
}


    