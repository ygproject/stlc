#include "smtp_server.h"

// The Email Sending data object contains config and data to send
SMTPData smtpData;

/*
 *  Callback function to get the Email sending status
 */
void sendCallback(SendStatus msg) 
{
  //Print the current status
  Serial.println(msg.info());
}

/*
 * email sending function. gets message as input
 */
void sendEmail(String msg) 
{
  // Preparing email
  Serial.println("Sending email...");
  // Set the SMTP Server Email host, port, account and password
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
  
  // Set the sender name and Email
  smtpData.setSender("ESP32-CAM", emailSenderAccount);
  
  // Set the subject
  smtpData.setSubject(emailSubject);
    
  // Set the email message in HTML format
  smtpData.setMessage(msg, true);

  // Add recipients, can add more than one recipient
  smtpData.addRecipient(emailRecipient1);
  smtpData.addRecipient(emailRecipient2);
  smtpData.setSendCallback(sendCallback);
  
  // Start sending Email, can be set callback function to track the status
  if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  // Clear all data from Email object to free memory
  smtpData.empty();
}
