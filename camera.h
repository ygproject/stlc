#define CAMERA_MODEL_AI_THINKER
#include "esp_camera.h"
#include "Arduino.h"
#include "RTClib.h"
#include "secrets.h"
#include <WiFi.h>
#include "logger.h"
extern RTC_DATA_ATTR int pictureNumber;
extern RTC_DATA_ATTR int bootCount;

/*
  voltage test function
*/
void voltageTest();
 
/*
   led operating function
*/
void measureLight();

/**
   configuration function
*/
void configInitCam();

/*
   configuration function
*/
void deepSleepFunc();

/*
   SD card initialising
*/
void initMicroSDCard();

/*
   wifi function
*/
void takeSavePhoto(int indicator);


/*
   wifi function
*/
void wifiCon();
