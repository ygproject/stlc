#define CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"
#include "esp_camera.h"
#include "Arduino.h"
#include "RTClib.h"
#define EEPROM_SIZE 1
extern RTC_DATA_ATTR int pictureNumber;
extern RTC_DATA_ATTR int bootCount;
#include <EEPROM.h>            
#include <WiFi.h>
#include "logger.h"
const long interval = 5000;   
static const char* ssid;
static char* password;

//gpio definitions
#define LED_GPIO_NUM 33
#define LED_PWM_CHANNEL 
#define LED_PWM_FREQ 5000
#define LED_PWM_BITS 10
#define LED_MAX_BRIGHTNESS 100
#define EEPROM_SIZE 1

//light sensor
static int sensorPin = 33;
static int sensorSw = 1;
static const int ledSw = 3;
static int lightInit;  // initial value
static int lightVal;   // light reading

#define TIME_TO_SLEEP 10   /* Time ESP32 will go to sleep (in seconds) */
#define uS_TO_S_FACTOR 1000000ULL  /* Conversion factor for micro seconds to seconds */

//unsigned long previousMillis = 0;     
//int measure_light();

/**
 * configuration function
 */
void configInitCam();

/*
 * configuration function
 */
void print_wakeup_reason();

/*
 * configuration function
 */
void deep_sleep();
 
/*
 * SD card initialising
 */
void initMicroSDCard();

/*
 * wifi function
 */
void takeSavePhoto();
 
/*
 * wifi function
 */
//void camera_set_led(uint8_t brightness);

/*
 * wifi function
 */
void wifi_con();
/*
 * 
 */
//void send_log();
