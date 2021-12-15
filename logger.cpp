#include "logger.h"
#include "camera.h"


void logger()
{
  String dataMessage= ("log entry_" + String(bootCount)+ " \r\n");
  digitalWrite(4, LOW);
  if(wifiSwitch == 1)
  {
    if(bootCount != 0 && bootCount % EMAIL_TIMING == 0)
    {
      //add maybe struct for errors.
      String emailMessage = "life sign for boot number: " + String(bootCount);

      wifiCon();
      sendEmail(emailMessage,(pictureNumber-1));
      WiFi.mode( WIFI_MODE_NULL );
    }
  }
}
