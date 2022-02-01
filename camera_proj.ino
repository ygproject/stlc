#include "camera.h"

/*
 * main
 */
void setup()
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  configInitCam();
}

/*
 * loop
 */
void loop()
{
  voltageTest();
  initMicroSDCard();
  measureLight();
  logger();
  deepSleepFunc();
}
