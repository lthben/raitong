/* Raitong farm prototype
 * 
 * Date: Dec 2017
 * Description: Case of missing goods stolen from truck. 
 * GPS tracking and logging of truck journey, RFID tracking
 * of boxes on the truck. You can sms to get the current location and 
 * status of the RFID tags. A sms alert is automatically sent 
 * if a tag goes missing.
 * 
 * Not all pins on the Mega and Mega 2560 support change interrupts, 
 * so only the following can be used for RX: 10, 11, 12, 13, 14, 15, 
 * 50, 51, 52, 53, A8 (62), A9 (63), A10 (64), A11 (65), A12 (66), 
 * A13 (67), A14 (68), A15 (69).
 * 
 * Arduino Mega connections:- 
 * Pin 10 - GPS shield TX
 * Pin 11 - GPS shield RX
 * Pin 7 - button switch
 * Pin 5 - Fona_RST (unconnected)
 * Pin 14 (TBC) - RFID shield Pin 
 * Pin 15 (TBC) - RFID shield Pin 3
 * Gnd - common ground (RFID gnd, GPS shield Gnd, phone bank Gnd, SD card Gnd)
 * 
 * GPS shield connections:-
 * 5V - phone bank 5V
 * Gnd - common ground
 * 
 * SD card connection:-
 * MOSI - Arduino pin 51
 * MISO - Arduino pin 50
 * SCK - Arduino pin 52 (also known as CLK or clock)
 * SS - Arduino pin 4 (also known as CS or chip select)
 * 5V - Arduino 5V 
 * Gnd - common ground
 * 
 * NOTE:
 * - The Adafruit fona library has been altered to also return date and time data in getGPS()
 * - Can use the another program "raitong_FONAtest.ino" to run tests
 * 
 */
