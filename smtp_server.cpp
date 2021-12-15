#include "smtp_server.h"

// The Email Sending data object contains config and data to send
SMTPData smtpData;

// Callback function to get the Email sending status
/*
 * 
 */
void sendCallback(SendStatus msg) 
{
  //Print the current status
  Serial.println(msg.info());
}

/*
 * 
 */
void sendEmail(String msg, int i) 
{
    //send email
  Serial.println("Sending email...");
  //Set the Email host, port, account and password
  smtpData.setLogin("smtp.gmail.com", 587, emailSenderAccount, emailSenderPassword);
  
  //Set the sender name and Email
  smtpData.setSender("ESP32-CAM", emailSenderAccount);
  
  //Set Email priority or importance High, Normal, Low or 1 to 5 (1 is highest)
  smtpData.setPriority("Normal");

  //Set the subject
  smtpData.setSubject("THIS IS OUR CODE - ESP32-CAM");
    
  //Set the message - normal text or html format
  smtpData.setMessage("<div style=\"color:#003366;font-size:20px;\">Image captured and attached.</div>", true);

  //Add recipients, can add more than one recipient
  smtpData.addRecipient(emailRecipient1);
  smtpData.addRecipient(emailRecipient2);
  String path = "/photos/picture_" + String(i) + ".jpg";
  //Add attach files from SD card
  smtpData.addAttachFile(path);
  
  //Set the storage types to read the attach files (SD is default)
  smtpData.setFileStorageType(MailClientStorageType::SD);
  
  smtpData.setSendCallback(sendCallback);
  
  //Start sending Email, can be set callback function to track the status
  if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  //Clear all data from Email object to free memory
  smtpData.empty();
}
