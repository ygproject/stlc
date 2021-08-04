#include "FS.h"                // SD Card ESP32
#include "SD_MMC.h"            // SD Card ESP32
#include "soc/soc.h"           // Disable brownour problems
#include "soc/rtc_cntl_reg.h"  // Disable brownour problems
#include "driver/rtc_io.h"
#include "time.h"
#include "smtp_server.h"
#define EMAIL_TIMING 2

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
