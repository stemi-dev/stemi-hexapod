#include <Arduino.h>
#include <Wire.h>
#include <WireSlave.h>
#include <WireSlaveRequest.h>

#include "SharedData.h"

#define SDA_PIN 23
#define SCL_PIN 22
#define I2C_SLAVE_ADDR 0x60

bool is_master = false;
bool is_setup = false;

#define MAX_SLAVE_RESPONSE_LENGTH 32


void setupI2cMaster()
{
  Wire.begin(SDA_PIN, SCL_PIN);
  Serial.println("I2C master init successful");
}
static unsigned long lastReadMillis = 0;
static byte x = 0;

void loopI2cMaster()
{

  delay(500);

  WireSlaveRequest slaveReq(Wire, I2C_SLAVE_ADDR, MAX_SLAVE_RESPONSE_LENGTH);

  slaveReq.setRetryDelay(1);

  bool success = slaveReq.request();

  if (success)
  {
    String msg = "";
    String parts[100] = {""};
    int partCounter = 0;
    while (1 < slaveReq.available())
    {
      char c = slaveReq.read();
      Serial.print(c);
      msg += c;
      if (c == ' ')
      {
        partCounter += 1;
        parts[partCounter] = "";
      }
      else
      {
        parts[partCounter] += c;
      }
    }
    Serial.println("partCounter");
    Serial.println(partCounter);
    if (partCounter >= 1)
    {
      String key = parts[0];
      int value = parts[1].toInt();
      Serial.print(key);
      Serial.print(" -> ");
      Serial.print(value);
      Serial.println("parts[1]");
      Serial.println(parts[1]);
      robot.i2cConnection = true;
      if (key == "linearVelocity")
      {
        robot.btInputData.linearVelocity = value;
      }
      else if (key == "direction")
      {
        robot.btInputData.direction = value;
      }
      else if (key == "angularVelocity")
      {
        robot.btInputData.angularVelocity = value;
      }
    }
    int x = slaveReq.read();
  }
  else
  {
    // if something went wrong, print the reason
  }
}

static byte y = 0;

void requestEvent()
{
  Serial.println("requestEvent");
  if (y % 3 == 0)
  {
    WireSlave.print("linearVelocity 10 ");
  }
  else if (y % 3 == 1)
  {
    WireSlave.print("direction 0 ");
  }
  else if (y % 3 == 2)
  {
    WireSlave.print("angularVelocity 0 ");
  }
  y += 1;
}

void setupI2cSlave()
{
  bool success = WireSlave.begin(SDA_PIN, SCL_PIN, I2C_SLAVE_ADDR);
  if (!success)
  {
    Serial.println("I2C slave init failed");
    while (1)
    {
      delay(100);
    }
  }
  else
  {
    Serial.println("I2c slave init successful");
  }

  WireSlave.onRequest(requestEvent);
}

void loopI2cSlave()
{
  WireSlave.update();
  delay(1);
}

void setupI2c()
{
  if (is_setup)
  {
    return;
  }
  if (is_master)
  {
    setupI2cMaster();
  }
  else
  {
    setupI2cSlave();
  }
  is_setup = true;
}

void loopI2c()
{
  setupI2c();
  if (is_master)
  {
    loopI2cMaster();
  }
  else
  {
    loopI2cSlave();
  }
}
