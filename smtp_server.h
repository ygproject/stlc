#include "arduino.h"
#include "ESP32_MailClient.h"
#include "secrets.h"

#define emailSenderAccount    SENDER_ACCOUNT
#define emailSenderPassword   SENDER_PASS
#define smtpServer            SMTP_SRV
#define smtpServerPort        SMTP_PORT
#define emailSubject          EMAIL_SUB
#define emailRecipient1       RECIPIENT1
#define emailRecipient2       RECIPIENT2

/*
 * 
 */
void sendCallback(SendStatus msg);

/*
 * 
 */
void sendEmail(String emailMessage);
