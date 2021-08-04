#include "logger.h"
#include "camera.h"

/*
 * 
 */
void createDir(fs::FS &fs, const char * path)
{
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path))
      {
          Serial.println("Dir created");
      } 
    else 
      {
          Serial.println("mkdir failed");
      }
}
/*
 * read file func
 */
int readFile(fs::FS &fs, const char * path)
{
    Serial.printf("Reading file: %s\n", path);
    File file = fs.open(path);
    if(!file)
    {
      Serial.println("Failed to open file for reading");
      return 1;
    }
    return 0;
}



void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
   //fwrite(fb->buf, 1, fb->len, file);
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
}

//Append to the end of file in SD card
/*
 * 
 */
void appendFile(fs::FS &fs, const char * path, const char * message)
{
    Serial.printf("Appending to file: %s\r\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message))
    {
        Serial.println("Message appended");
    } else
    {
        Serial.println("Append failed");
    }
}

/*
 * 
 */
void logger()
{
  String dataMessage= ("log entry " + String(bootCount)+ " \r\n");
  if(readFile(SD_MMC, "/log.txt"))
  {
    writeFile(SD_MMC, "/log.txt", dataMessage.c_str());
    }
  else
  {
    appendFile(SD_MMC, "/log.txt", dataMessage.c_str());
  }
  if(bootCount != 0 && bootCount % EMAIL_TIMING == 0)
  {
    //add maybe struct for errors.
    String emailMessage = "daily life sign for boot number" + String(bootCount);
    wifi_con();
    send_email(emailMessage);
    Serial.println("number ten!!!");
  }
}
