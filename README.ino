/* Raitong farm prototype
 * 
 * Author: Benjamin Low (ben@sl2square.org)
 * Date: Dec 2017
 * Description: Case of missing goods stolen from truck. 
 * GPS tracking and logging of truck journey, RFID tracking
 * of boxes on the truck. You can sms to get the current location and 
 * status of the RFID tags. A sms alert is automatically sent 
 * if a tag goes missing.
 * 
 * Arduino Mega connections:- 
 * Pin 10 - GPS shield TX
 * Pin 11 - GPS shield RX
 * Pin 7 - button switch
 * Pin 5 - Fona_RST (unconnected)
 * Pin 12 - RFID shield Pin 2
 * Pin 13 - RFID shield Pin 3
 * Gnd - common ground (RFID gnd, GPS shield Gnd, phone bank Gnd, SD card Gnd)
 * 
 * GPS shield connections:-
 * 5V - phone bank 5V
 * Gnd - common ground
 * 
 * SD card connections:-
 * MOSI - Arduino pin 51
 * MISO - Arduino pin 50
 * SCK - Arduino pin 52 (also known as CLK or clock)
 * SS - Arduino pin 4 (also known as CS or chip select)
 * 5V - Arduino 5V 
 * Gnd - common ground
 * 
 * RFID reader connections:-
 * 5V - phone bank 5V
 * Gnd - phone bank Gnd
 * Gnd - Common ground
 * 
 */
