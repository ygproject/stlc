#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"
#include "esp_camera.h"
#include "camera.h"
#include "logger.h"
#include "smtp_server.h"        

/*
 * main
 */
void setup() 
///camera definiton
{
  Serial.begin(115200);
  Serial.setDebugOutput(true);
  Serial.println();
  configInitCam();
  initMicroSDCard();
  wifi_con();
  logger();
  takeSavePhoto();
  delay(1000);
  deep_sleep();
} 

void loop(){}
