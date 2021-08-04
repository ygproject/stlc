#include "smtp_server.h"

// The Email Sending data object contains config and data to send
SMTPData smtpData;

// Check if photo capture was successful
//bool checkPhoto( fs::FS &fs ) {
//  File f_pic = fs.open( FILE_PHOTO );
//  unsigned int pic_sz = f_pic.size();
//  return ( pic_sz > 100 );
//}

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
void send_email(String msg) 
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
  // Set the email message in text format
  //smtpData.setMessage("Photo captured with ESP32-CAM and attached in this email.", false);

  // Add recipients, can add more than one recipient
  smtpData.addRecipient(emailRecipient1);
  smtpData.addRecipient(emailRecipient2);

  // Add attach files from SPIFFS
//  smtpData.addAttachFile(FILE_PHOTO, "image/jpg");
  // Set the storage type to attach files in your email (SPIFFS)
//  smtpData.setFileStorageType(MailClientStorageType::SPIFFS);

  smtpData.setSendCallback(sendCallback);
  
  // Start sending Email, can be set callback function to track the status
  if (!MailClient.sendMail(smtpData))
    Serial.println("Error sending Email, " + MailClient.smtpErrorReason());

  // Clear all data from Email object to free memory
  smtpData.empty();
}
