#include <SoftwareSerial.h>

//set the log interval here
const unsigned int LOGINTERVAL = 5000;//max of 65000, the interval in ms between logging of GPS data

//button switch
const int buttonPin = 7; //the other button pin is connected to ground
int buttonReading, buttonState;
int lastButtonState = HIGH; //HIGH by default
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 5000;
int ledState = LOW;
const int ledPin = 13; //the LED on board the Arduino

//fona sms
#include "Adafruit_FONA.h"
#define FONA_RST 5
Adafruit_FONA_3G fona = Adafruit_FONA_3G(FONA_RST);
SoftwareSerial fonaSS(10, 11); // RX, TX
SoftwareSerial *fonaSerial = &fonaSS;
char replybuffer[255]; 
uint8_t readline(char *buff, uint8_t maxbuff, uint16_t timeout = 0); 
char fonaNotificationBuffer[64];          //for notifications from the FONA
char smsBuffer[250]; //to store the received sms message content
char replyMsg[128]; //to store the reply message to send

//SD card
#include <SPI.h>
#include <SD.h>
const int chipSelect = 4;
unsigned long lastLoggedTime;

void setup()
{
  setup_button();

  // Open serial communications to computer
  Serial.begin(115200); //NOTE: default: 115200, change to 9600 for serial monitor keyboard communication. 

  fonaSS.begin(9600); // Reconnect at lower baud, 115200 had issues with SoftwareSerial
  fonaSerial->begin(9600);

  fonaSS.println(F("AT+IPR=9600"));  // Set baud to 9600
  delay(100); // Let the command run

  if (! fona.begin(*fonaSerial)) {
    Serial.println(F("Couldn't find FONA"));
    while (1);
  }
  Serial.println(F("FONA is OK"));

  //Clear out any waiting serial data
  while (fonaSS.available())
  {
    fonaSS.read();
  }

  Serial.println(F("Raitong system activated."));
  //  fonaSS.println("AT+CMGSO=\"97974063\",\"Raitong system activated\"");
  delay(100);
  fonaSS.println(F("AT+CGPS?"));
  delay(100);
  fonaSS.println(F("AT+CGPS=1,1")); //activate GPS tracking
  delay(100);
  fonaSS.println(F("AT+CTZU=1"));
  Serial.println(F("Automatic time zone updating turned on"));
  Serial.println(F("Starting GPS tracking, allow up to 15min to get initial fix"));

  delay(100);

  fonaSerial->print(F("AT+CNMI=2,1\r\n"));  //set up the FONA to send a +CMTI notification when an SMS is received

  fonaSS.println(F("AT"));
  Serial.println(F("FONA ready"));

  setup_SDcard();
}

void loop()
{
  //  button_operation(); //test whether tact button pressed

//    run_serial_ports();

  run_sms_system();   

  log_data();
}

void run_serial_ports() {
  //This loop just takes whatever comes in from the console and sends it to the board

  if (Serial.available())
  {
    fonaSS.write(Serial.read());
  }
  if (fonaSS.available())
  {
    Serial.write(fonaSS.read());
  }
}




