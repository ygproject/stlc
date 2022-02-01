#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "driver/rtc_io.h"
#include "smtp_server.h"
#include "constants.h"


/*
 * 
 */
void createDir(fs::FS &fs, const char * path);

/*
 * 
 */
int openFile(fs::FS &fs, const char * path);

/*
 * 
 */
int readFile(fs::FS &fs, const char * path);

/*
 * 
 */
void writeFile(fs::FS &fs, const char * path, const char * message);

/*
 * 
 */
void appendFile(fs::FS &fs, const char * path, const char * message);

/*
 * 
 */
void logger();
