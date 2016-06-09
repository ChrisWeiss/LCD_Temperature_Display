# LCD_Temperature_Display
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
The temperature sensors are OneWire, which means they will smartly share a single data pin.  
You need to connect the pullup resistor between the data lines on the temperature sensors and 5v.  
