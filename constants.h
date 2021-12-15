//deep sleep time
#define TIME_TO_SLEEP 60 
/* Time ESP32 will go to sleep (in seconds) */
#define uS_TO_S_FACTOR 1000000ULL
//number of cycles to send an email
#define EMAIL_TIMING 2
//turn wifi or on off
//extern int WIFI_SWTICH = 1;
//light threshold
#define V_THRESHOLD 3784
//
#define WIFI_THRESHOLD 3983
//
#define LIGHT_TRHESH 3846

#define WIFI_ON = 1;
#define WIFI_OFF = 0;

int WIFI_SWITCH;

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

#define RESULT_PIN 33
#define LED_PIN 0
#define SENSOR_PIN 16
