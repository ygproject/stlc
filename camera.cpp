#include "camera.h"
int bootCount = 0;
int pictureNumber = 0;
/*
 * configuration function
 */
void configInitCam()
{
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = Y2_GPIO_NUM;
  config.pin_d1 = Y3_GPIO_NUM;
  config.pin_d2 = Y4_GPIO_NUM;
  config.pin_d3 = Y5_GPIO_NUM;
  config.pin_d4 = Y6_GPIO_NUM;
  config.pin_d5 = Y7_GPIO_NUM;
  config.pin_d6 = Y8_GPIO_NUM;
  config.pin_d7 = Y9_GPIO_NUM;
  config.pin_xclk = XCLK_GPIO_NUM;
  config.pin_pclk = PCLK_GPIO_NUM;
  config.pin_vsync = VSYNC_GPIO_NUM;
  config.pin_href = HREF_GPIO_NUM;
  config.pin_sscb_sda = SIOD_GPIO_NUM;
  config.pin_sscb_scl = SIOC_GPIO_NUM;
  config.pin_pwdn = PWDN_GPIO_NUM;
  config.pin_reset = RESET_GPIO_NUM;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;
  //init with high specs to pre-allocate larger buffers
  if(psramFound())
    {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
    } 
  else 
    {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    }

//photo resistor control   
  pinMode(1, OUTPUT);
//led control 
  pinMode(3, OUTPUT);
//photoresistor result
  pinMode(33,  INPUT);

  // Turns off the ESP32-CAM white on-board LED (flash) connected to GPIO 4
  pinMode(4, OUTPUT);
  digitalWrite(4, LOW);
  // camera init
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK) 
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
  sensor_t * s = esp_camera_sensor_get();
  s->set_brightness(s, 2);     // -2 to 2
}



/*
 * wake up reason - maybe control function, maybe redunant
 */
void print_wakeup_reason()
{
  esp_sleep_wakeup_cause_t wakeup_reason;

  wakeup_reason = esp_sleep_get_wakeup_cause();

  switch(wakeup_reason)
  {
    case ESP_SLEEP_WAKEUP_EXT0 : Serial.println("Wakeup caused by external signal using RTC_IO"); break;
    case ESP_SLEEP_WAKEUP_EXT1 : Serial.println("Wakeup caused by external signal using RTC_CNTL"); break;
    case ESP_SLEEP_WAKEUP_TIMER : Serial.println("Wakeup caused by timer"); break;
    default : Serial.printf("Wakeup was not caused by deep sleep: %d\n",wakeup_reason); break;
  }
}

/*
 * deep sleep function - maybe redundant
 */
void deep_sleep()
{
  delay(1000);
  //Increment boot number and print it every reboot
  ++bootCount;
  print_wakeup_reason();
  Serial.println("Boot number: " + String(bootCount));
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
 
  Serial.println("Going to sleep now");
  delay(1000);
  esp_deep_sleep_start();
  Serial.println("This will never be printed");
  }

/*
 * SD card initialising
 */
void initMicroSDCard(){
  // Start Micro SD card
  Serial.println("Starting SD Card");
  if(!SD_MMC.begin("/sdcard", true))
  {
    Serial.println("SD Card Mount Failed");
    return;
  }
  uint8_t cardType = SD_MMC.cardType();
  if(cardType == CARD_NONE){
    Serial.println("No SD Card attached");
    return;
  }
  if(bootCount == 0)
  {
    createDir(SD_MMC, "/log_dir");
    Serial.println("folder created");
  }
  ++bootCount;
}

///*
// * set led brightness
// */
//void camera_set_led(uint8_t brightness)
//{
//  if(brightness > LED_MAX_BRIGHTNESS)
//  {
//    brightness = LED_MAX_BRIGHTNESS;
//  }
//  ledcWrite(LED_PWM_CHANNEL, brightness);
//}

//int measure_light()
//{
//  //take measurment
//  digitalWrite (sensorSw, HIGH);
//  delay(200);
//  //sampling
//  int lightInit = analogRead(sensorPin); 
//  //turning off light sensor
//  digitalWrite (ledSw, HIGH); // turn on light
//  if(lightVal - lightInit <  50)
//  {
//    digitalWrite (ledSw, HIGH); // turn on light
//    delay(200);
//    digitalWrite (ledSw, LOW); // turn off light
//  }  
//  else
//  {
//    digitalWrite (ledSw, LOW); // turn off light
//  }
//}
  
/*
 * picture function - change name of function
 */
void takeSavePhoto()
{
  EEPROM.begin(EEPROM_SIZE);
  String path = "/log_dir/picture" + String(pictureNumber) +".jpg";

  ///light_val =  measure light();
//  led_control();
  Serial.printf("Picture file name: %s\n", path.c_str());
  camera_fb_t  * fb = esp_camera_fb_get();
  if(!fb) 
  {
    Serial.println("Camera capture failed");
    return;
  }
  // Save picture to microSD card
  fs::FS &fs = SD_MMC; 
  File file = fs.open(path.c_str(), FILE_WRITE);
  if(!file){
    Serial.println("Failed to open file in writing mode");
  } 
  else 
  {
    file.write(fb->buf, fb->len); // payload (image), payload length
    Serial.printf("Saved file to path: %s\n", path.c_str());
    EEPROM.write(0, pictureNumber);
    EEPROM.commit();
  }
  file.close();
   pictureNumber++;
  //return the frame buffer back to the driver for reuse
  esp_camera_fb_return(fb); 
}

/*
 * wifi function
 */
void wifi_con()
{
  //connecting to wifi
  WiFi.mode(WIFI_STA);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);  
  while (WiFi.status() != WL_CONNECTED)
    {
    Serial.print(".");
    delay(500);
    }
  Serial.println();
  Serial.print("ESP32-CAM IP Address: ");
  Serial.println(WiFi.localIP()); 
  }

//void send_log()
//{
//  if(booter %10 == 0)
//  {
//  wifi_con();
//  smtp_config();
//  send_email();
//  }
//}
