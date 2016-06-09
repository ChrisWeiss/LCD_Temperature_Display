#include <OneWire.h>

/*
Arduino Dual Temperature LCD Display
Reads temp from two DS18B20 temperature sensors and displays to 2x16 character serial LCD


References:
https://www.sparkfun.com/tutorials/246
https://gist.github.com/brooksware2000/3628594
https://arduino-info.wikispaces.com/YourDuinoStarter_TemperatureSensor

Hardware:
Temperature Sensor DS18B20
Sparkfun Serial LCD
Arduino (I used a Duemilanove)
4.7k pullup resistor

Circuit Notes:
Most of it is fairly straightforward with the following notes:
The SparkFun LCD runs at 3.3v. If you tie it to 5v, you get a white screen.
The DS18B20 temperature sensors run at 5v.
The temperature sensors are OneWire, which means they will smartly share a single data pin.
You need to connect the pullup resistor between the data lines on the temperature sensors and 5v.
*/

/* Import needed libraries */
#include <OneWire.h> // For temp sensor communication
#include <DallasTemperature.h> // For the actual temp sensors
#include <SoftwareSerial.h> // Serial library to support LCD

/* Declare Constants */
#define ONE_WIRE_BUS 8 // Connect temp sensors to Pin 8
SoftwareSerial lcdSerial(3,2); // Attach the serial display's RX line to digital pin 2 Pin 2 = TX, pin 3 = RX (unused)

/* Declare objects */
OneWire ourWire(ONE_WIRE_BUS); // Set up a oneWire instance to communicate with any OneWire device
DallasTemperature sensors(&ourWire); // Tell Dallas Temperature Library to use oneWire Library

/* Declare Variables */
char buffer[4];

/* Application Setup */
void setup()
{
delay(1000); // Optional: Wait a few seconds for the panel to initialize
  lcdSerial.begin(9600); // Initialize serial port
delay(1000); // Optional: Wait a few seconds for the serial connection to initialize

/* The below code sets the static text that appears on the screen.
   Uncommenting the last two lines will set this text as the default
   LCD "splash screen", so it comes up automatically on boot.
   If you do that, you don't need to run the static display setup
   routine every time you start the app. Handy for embedded solutions.
   */

/* Sets the initial static display elements.
   Comment out if you save this as the splash screen
   */

//  lcdSerial.write(254); // Tell LCD we're about to position the cursor
//  lcdSerial.write(128); // Position cursor at first character.
//  lcdSerial.write("Coolant Temps(c)"); // clear display + legends
//  lcdSerial.write("In:     Out:    ");

/* Writes the current display as the default splash screen
   You would only need to run this once, then can comment it out.
   */
   
//  lcdSerial.write(0x7C); // Set new LCD splash
//  lcdSerial.write(0x0A); // Confirm setting new LCD splash

/* End static display setup
   */

  sensors.begin(); // Start up the DallasTemperature library

}

/* Main loop - Runs forever */
void loop()
{

  sensors.requestTemperatures(); // Send the command to get temperatures
  float temp_in = sensors.getTempCByIndex(0); // Read probe 0 into temp_in as a float
  float temp_out = sensors.getTempCByIndex(1); // Read probe 1 into temp_out as a float

  lcdSerial.write(254); // Tell LCD we're about to position the cursor
  lcdSerial.write(195); // Position cursor at character 4 on line 2
  lcdSerial.print(dtostrf(temp_in, 4, 1, buffer)); // Write text version of temp_in 4 characters long (to the 1st decimal place)

  lcdSerial.write(254); // Tell LCD we're about to position the cursor
  lcdSerial.write(204); // Position cursor at character 13 on line 2
  lcdSerial.print(dtostrf(temp_out, 4, 1, buffer)); // Write text version of temp_out 4 characters long (to the 1st decimal place)

}

