void setup_SDcard() {
  Serial.print(F("Initializing SD card..."));

  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println(F("Card failed, or not present"));
    // don't do anything more:
    return;
  }
  Serial.println(F("card initialized."));
}

void log_data() {

    String dataString = "";

    if (millis() - lastLoggedTime > LOGINTERVAL) {

        dataString += get_gps_reading();
        Serial.print("datastring: ");
        Serial.println(dataString);
        
        File dataFile = SD.open("datalog.txt", FILE_WRITE);

        if (dataFile) {
            dataFile.println(dataString);
            dataFile.close();

            Serial.print(F("Writing to file: "));
            Serial.println(dataString);
        } else {
            Serial.println(F("error opening datalog.txt"));
        }
        lastLoggedTime = millis();
    }
}

