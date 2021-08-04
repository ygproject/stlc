#define CAMERA_MODEL_AI_THINKER
#include "esp_camera.h"
#include "Arduino.h"
#include "RTClib.h"
#include "secrets.h"
#define EEPROM_SIZE 1
extern RTC_DATA_ATTR int pictureNumber;
extern RTC_DATA_ATTR int bootCount;
#include <EEPROM.h>
#include <WiFi.h>
#include "logger.h"

//gpio definitions
#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#define LED_GPIO_NUM 33
#define LED_PWM_CHANNEL
#define LED_PWM_FREQ 5000
#define LED_PWM_BITS 10
#define LED_MAX_BRIGHTNESS 100
#define EEPROM_SIZE 1

//light sensor
static int resultPin = 33;
static int sensorPin = 0;
static const int ledPin = 16;
static int lightInit;  // initial value
static int lightVal;   // light reading
static int Analog = 0;
static unsigned long Sum = 0;
static unsigned long Average = 0;


#define TIME_TO_SLEEP 10   /* Time ESP32 will go to sleep (in seconds) */
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */
/*
   led operating function
*/
int measure_light();

/**
   configuration function
*/
void configInitCam();

/*
   configuration function
*/
void deep_sleep();

/*
   SD card initialising
*/
void initMicroSDCard();

/*
   wifi function
*/
void takeSavePhoto();

/*
   led function
*/
//void camera_set_led(uint8_t brightness);

/*
   wifi function
*/
void wifi_con();
