#include "arduino.h"
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include "ESP32_MailClient.h"
#define emailSenderAccount    ""
#define emailSenderPassword   ""
#define smtpServer            ""
#define smtpServerPort        0
#define emailSubject          "[ALERT] ESP32 log"

/*
 * smtp server + email functions
 */
//////////////////////////////////////////////////////////////////////////////////////////////
// Default Recipient Email Address
static String inputMessage = "";
//static String inputMessage = "";
static String enableEmailChecked = "checked";
//boot number or camera number
static String inputMessage2 = "true";
// int variable - camera status
static String inputMessage3 = "25.0";

void notFound(AsyncWebServerRequest *request);

String processor(const String& var);

void smtp_config();

bool sendEmailNotification(String emailMessage);
// Callback function to get the Email sending status
void sendCallback(SendStatus msg);

void send_email();
