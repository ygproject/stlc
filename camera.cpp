#include "camera.h"
int bootCount = 0;
int pictureNumber = 0;
int wifiSwitch = 1;
char * ssid = WIFI_NAME;
char * password = WIFI_PASSWORD;
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
////2640_FRAME_SIZE
  config.frame_size = FRAMESIZE_UXGA;
////5640_FARME_SIZE 
//  config.frame_size = FRAMESIZE_QSXGA;

    config.jpeg_quality = 10;
    config.fb_count = 2;
    } 
  else 
    {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
    }
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_ON);

//photo resistor control   
  pinMode (SENSOR_PIN, OUTPUT);
//led control 
  pinMode (LED_PIN, OUTPUT);
//photoresistor result
  pinMode(RESULT_PIN,  INPUT);
  
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
  //Sensor settings
  sensor_t * s = esp_camera_sensor_get();
  
// 2640 settings
  s->set_vflip(s, 1); // flip it back
  s->set_brightness(s, -1); // up the brightness just a bit
  s->set_saturation(s, 1); // lower the saturation
  s->set_contrast(s, 1);       // -2 to 2
  s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
  s->set_wb_mode(s, 1);        // 0 to 4 - if awb_gain enabled (0 - Auto, 1 - Sunny, 2 - Cloudy, 3 - Office, 4 - Home)
  s->set_aec2(s, 0);           // 0 = disable , 1 = enable
  s->set_ae_level(s, 0);       // -2 to 2
  s->set_aec_value(s, 200);    // 0 to 1200
  s->set_gain_ctrl(s, 0);      // 0 = disable , 1 = enable
  s->set_agc_gain(s, 1);       // 0 to 30
  s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
  s->set_dcw(s, 0);            // 0 = disable , 1 = enable 

//// 5640 settings
//  s->set_brightness(s, 1);     // -2 to 2
//  s->set_contrast(s, 1);       // -2 to 2
//  s->set_saturation(s, 0);     // -2 to 2
//  s->set_special_effect(s, 0); // 0 to 6 (0 - No Effect, 1 - Negative, 2 - Grayscale, 3 - Red Tint, 4 - Green Tint, 5 - Blue Tint, 6 - Sepia)
//  s->set_whitebal(s, 0);       // 0 = disable , 1 = enable
//  s->set_awb_gain(s, 1);       // 0 = disable , 1 = enable
//  s->set_wb_mode(s, 1);        // 0 to 4 - if awb_gain enabled (0 - Auto, 1 - Sunny, 2 - Cloudy, 3 - Office, 4 - Home)
//  s->set_exposure_ctrl(s, 0);  // 0 = disable , 1 = enable
//  s->set_aec2(s, 0);           // 0 = disable , 1 = enable
//  s->set_ae_level(s, 2);       // -2 to 2
//  s->set_aec_value(s, 200);    // 0 to 1200
//  s->set_gain_ctrl(s, 0);      // 0 = disable , 1 = enable
//  s->set_agc_gain(s, 3);       // 0 to 30
//  s->set_gainceiling(s, (gainceiling_t)0);  // 0 to 6
//  s->set_bpc(s, 0);            // 0 = disable , 1 = enable
//  s->set_wpc(s, 0);            // 0 = disable , 1 = enable
//  s->set_raw_gma(s, 1);        // 0 = disable , 1 = enable
//  s->set_lenc(s, 0);           // 0 = disable , 1 = enable
//  s->set_hmirror(s, 0);        // 0 = disable , 1 = enable
//  s->set_vflip(s, 1);          // 0 = disable , 1 = enable
//  s->set_dcw(s, 0);            // 0 = disable , 1 = enable
//  s->set_colorbar(s, 0);       // 0 = disable , 1 = enable
}

/*
 *Voltage monitoring function
 */
void voltageTest()
{  
  int Analog = analogRead(RESULT_PIN); 
  if(Analog < V_THRESHOLD)
  {
    Serial.println("Low Voltage");
    esp_deep_sleep_start();
  } 
  if(Analog < WIFI_THRESHOLD)
  {
    wifiSwitch = WIFI_OFF; 
    Serial.println("Voltage to low for wifi");
  }
  else
  {
    wifiSwitch = WIFI_ON;
    Serial.println("Voltage OK");
  }
}

/*
 * deep sleep function - maybe redundant
 */
void deepSleepFunc()
{
  //Increment boot number and print it every reboot
  ++bootCount;
  Serial.println("Boot number: " + String(bootCount));
  Serial.println("Setup ESP32 to sleep for every " + String(TIME_TO_SLEEP) +
  " Seconds");
  esp_deep_sleep_start();
}

/*
 * SD card initialising
 */
void initMicroSDCard()
{
  if (digitalRead(4) == LOW)
  {
  // turn LED on
    digitalWrite(LED_PIN, HIGH);
  }
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
  //add condition for existing dir.
  {
    createDir(SD_MMC, "/photos");
    Serial.println("folder created");
  }
}



/*
 * light measuring function
 */
void measureLight()
{
  int Analog = 0;
  long Sum = 0;
  long Average = 0;
  digitalWrite (SENSOR_PIN, 0);  // turn on photoresistor
  Serial.println("photo on");
  for (int i = 0; i < 100; i++)
  {
    Analog = analogRead(RESULT_PIN); 
  
    Sum = Sum + Analog;   //Sum for averaging
    
    Average = (Sum/100);
  }
  Serial.println("light_sensor_val = ");
  Serial.println(Average);
  digitalWrite (RESULT_PIN, HIGH); // turn off photoresistor
  Serial.println("photo off");
  int ind = (Average > LIGHT_TRHESH)? ind = 1: ind = 0;
  takeSavePhoto(ind);
}

  
/*
 * picture function - change name of function
 */
void takeSavePhoto(int indicator)
{
  String path = "/photos/picture_" + String(pictureNumber) + ".jpg";
  if(indicator)
  {
    Serial.println("Turning on LED");
    digitalWrite (LED_PIN, HIGH);  // turn on the LED
  }
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
  if(!file)
  {
    Serial.println("Failed to open file in writing mode");
  } 
  else 
  {
    file.write(fb->buf, fb->len); // payload (image), payload length
    Serial.printf("Saved file to path: %s\n", path.c_str());
  }
  file.close();
  if(indicator)
  {
  Serial.println("Turning off LED");
  digitalWrite(LED_PIN, LOW); // turn off the LED
  }
  pictureNumber++;
  //return the frame buffer back to the driver for reuse
  esp_camera_fb_return(fb); 
  
}

/*
 * wifi function
 */
void wifiCon()
{
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
  Serial.println("WiFi connected");
}
