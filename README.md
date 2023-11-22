# STEMI hexapod v3 #

v1 and v2 on other branch

## For expansion board
```cpp
#include "Hexapod.h"
#include "ExpansionDriver.h"

SharedData robot;
Hexapod hexapod;

void setup()
{
	Serial.begin(9600);
	hexapod.init();
	robot.setLed(GREEN);
	robot.setHeight(50);
}

void loop()
{
	ExpansionDriver expansionDriver;
	delay(2000);
	robot.setLedStatic(6, BLUE);
	expansionDriver.init();
	while (true)
	{
		expansionDriver.readSHT();
		delay(100);
		Serial.println(expansionDriver.degC);
		Serial.println(expansionDriver.humidity);
		delay(1000);
		expansionDriver.readDistance(1);
		delay(100);
		Serial.println(expansionDriver.distance_center);
		delay(1000);
	}
}
```

Library that includes everything you need to get your STEMI hexapod walking and dancing using your mobile app :)

### Prepare your Arduino IDE for programming esp32 ###

1. Install FTDI driver: <https://learn.sparkfun.com/tutorials/how-to-install-ftdi-drivers/all> (Windows should do it automatically)
2. Install Arduino core for esp32: <https://github.com/espressif/arduino-esp32>

### Install the libraries ###

1. Install NeoPixelBus library: <https://github.com/Makuna/NeoPixelBus>
2. Install STEMI-hexapod library: <https://github.com/stemi-education/stemi-hexapod> (this library)  
Note: We recommend installing these libraries via Arduino Library Manager.

### Program the robot ###

1. Open Arduino IDE
2. Choose "ESP32 Dev Module" board
3. Open "File > Examples > STEMI-hexapod > Default"
4. Upload to your STEMI hexapod robot

For writing your own code replace last two steps with:

3. Open "File > Examples > STEMI-hexapod > Empty-user-mode"
4. Use STEMI-hexapod API to program the robot and make it move and glow as you please :)
    * API documentation is available on the following link: <https://github.com/stemi-education/stemi-hexapod/blob/devel/APIDocumentation.md>.
