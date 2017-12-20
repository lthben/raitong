String get_gps_reading() {

  float latitude, longitude, rtc_date, rtc_time, speed_kph;

  boolean gps_success = fona.getGPS(&latitude, &longitude, &rtc_date, &rtc_time, &speed_kph);

  if (gps_success) {

    //    Serial.print(str1);
    //    Serial.println(latitude, 6);
    //    Serial.print(str2);
    //    Serial.println(longitude, 6);

    //    Serial.print("GPS speed MPH:");
    //    speed_mph = speed_kph * 0.621371192;
    //    Serial.println(speed_mph);

    //    Serial.print(str3);
    //    Serial.println(rtc_date, 0); //no decimal points
    //    Serial.print(str4);
    //    Serial.println(rtc_time, 0);
    //    Serial.print(str5);
    //    Serial.println(speed_kph);

    //    Serial.print("GPS heading:");
    //    Serial.println(heading);
    //    Serial.print("GPS altitude:");
    //    Serial.println(altitude);

    return ("date(ddmmyy):" + String(rtc_date, 0) + " UTC time(hhmmss):" + String(rtc_time, 0) + " latlon:" + String(latitude, 6) + "," + String(longitude, 6) + " speed(kph):" + String(2.0*speed_kph, 2) );

  } else {
    Serial.println(F("Waiting for FONA GPS 3D fix..."));

    return "waiting for GPS fix";
  }
}


