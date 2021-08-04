#include "camera.h"
#include "logger.h"

/*
   main
*/
void setup()
{
  Serial.begin(9600);
  Serial.setDebugOutput(true);
  Serial.println();
  configInitCam();
}

void loop()
{
  initMicroSDCard();
  measure_light();
  logger();
  deep_sleep();
}
