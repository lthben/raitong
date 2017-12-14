void run_sms_system() {
  char* bufPtr = fonaNotificationBuffer;    //handy buffer pointer

  if (fona.available())      //any data available from the FONA?
  {
    int slot = 0;            //this will be the slot number of the SMS
    int charCount = 0;
    //Read the notification into fonaInBuffer
    do  {
      *bufPtr = fona.read();
      Serial.write(*bufPtr);
      delay(1);
    } while ((*bufPtr++ != '\n') && (fona.available()) && (++charCount < (sizeof(fonaNotificationBuffer) - 1)));

    //Add a terminal NULL to the notification string
    *bufPtr = 0;

    //Scan the notification string for an SMS received notification.
    //  If it's an SMS message, we'll get the slot number in 'slot'
    if (1 == sscanf(fonaNotificationBuffer, "+CMTI: " FONA_PREF_SMS_STORAGE ",%d", &slot)) {
      Serial.print(F("slot: ")); Serial.println(slot);

      char callerIDbuffer[32];  //we'll store the SMS sender number in here

      // Retrieve SMS sender address/phone number.
      if (! fona.getSMSSender(slot, callerIDbuffer, 31)) {
        Serial.println(F("Didn't find SMS message in slot!"));
      }
      Serial.print(F("FROM: ")); Serial.println(callerIDbuffer);

      // Retrieve SMS value.
      uint16_t smslen;
      if (fona.readSMS(slot, smsBuffer, 250, &smslen)) { // pass in buffer and max len!
        Serial.print(F("message content received: "));
        Serial.println(smsBuffer);
      }

      //Send back an automatic response
      Serial.println("Sending reponse...");
      if (String(smsBuffer) == "Loc") {
        get_gps_reading().toCharArray(replyMsg, 128);
      } else if (String(smsBuffer) == "Tags") {
        String(F("here are the tags")).toCharArray(replyMsg, 128);
      } else {
        String(F("Unrecognized command. Available commands: 'Loc' (get location), 'Tags' (get tag info)")).toCharArray(replyMsg, 128);;
      }

      if (!fona.sendSMS(callerIDbuffer, replyMsg)) {
        Serial.println(F("Failed"));
      } else {
        Serial.println(F("Sent!"));
      }

      // delete the original msg after it is processed
      //   otherwise, we will fill up all the slots
      //   and then we won't be able to receive SMS anymore
      if (fona.deleteSMS(slot)) {
        Serial.println(F("OK!"));
      } else {
        Serial.print(F("Couldn't delete SMS in slot ")); Serial.println(slot);
        fona.print(F("AT+CMGD=?\r\n"));
      }
    }
  }
}

