#include <SoftwareSerial.h>
SoftwareSerial mySerial(2, 3); // RX, TX

void setup()
{
  // Open serial communications to computer
  Serial.begin(115200);

  mySerial.begin(115200); // Default for the board
  mySerial.println("AT+IPR=57600");  // Set baud to 57600
  delay(100); // Let the command run
  mySerial.begin(57600); // Reconnect at lower baud, 115200 had issues with SoftwareSerial
  
  //Clear out any waiting serial data
  while (mySerial.available())
  {
    mySerial.read();
  }
  mySerial.println("AT");
}

void loop()
{
  /*
   * This loop just takes whatever comes in from the console and sends it to the board
   */
  if (Serial.available())
  {
    mySerial.write(Serial.read());
  }
  if (mySerial.available())
  {
    Serial.write(mySerial.read());
  }
}
