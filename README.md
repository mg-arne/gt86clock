# Scion FRS / Subaru BRZ / Toyota GT86 Enhanced Clock

## About
GT86clock is a display, which replaces the stock clock of an Scion FRS / Subaru BRZ / Toyota GT86.

It shows the:
* time
* oil tempurature
* coolant tempurature
* oil pressure
* voltage
* Lambda/AFR
while looking completey stock at the first glance.

There is also a web server running, where you can get a view trending data of the last couple of hours the engine ran.

## Disclaimer & Background
I'm not a car mechanic nor a software developer. I bought my GT86 with a broken engine and replaced it with a new to me one. As many other Subaru engines the con rod bearings disintegrate from the lack of lubrication.
Oil temperature and oil pressure seems to be decent indications of the engine health, but unfortunately in stock form there is no way to keep an eye on those metrics. That is how this project started.

## Demo
![Demo](../assets/assets/gt86clock_demo.gif)

## Credits
Somebody else had the *ingenious* idea to reuse the clock location. Kudos to her/him!
There are few similar projects out there. I only looked at them very briefly, I enjoyed the challenge to build my own version.

## Picture
My test rig so I test the code outside of the car.
![testrig](../assets/assets/gt86clock_testrig.jpg)

Start up logo: It does not have any function. It just looks cool.
![startup](../assets/assets/gt86clock_startup.jpg)

Clock with small logo
![time](../assets/assets/gt86clock_time.jpg)

One of the data views:
![temp](../assets/assets/gt86clock_temp.jpg)

## How does it work
An ESP8266 is reading the following data:
- oil temp, water temp, volts and AFR via a CAN bus module connected to the OBD2 port
- oil pressure using a pressure sensor replacing the OEM oil pressure switch
- a real time clock module to keep track of time
- 3 micro switches (due to the lack of input pins on the ESP they are connected to only 2 input pins using two diodes)

What used to be AM/PM button is changing the views new. A long press is either changing the units or in case of the clock view it fetches the current time via NTP. The "H" and "M" buttons are remaining as before.

## Views
1. logo: useless start up screen
2. clock: time + small logo
3. oil temperature: single display, value read from CAN
4. water temperature: single display, value read from CAN
5. oil+water temperature: dual display, value read from CAN
6. oil pressure: single display, value read from pressure sensor connected to the analog input pin
7. AFR+voltage: dual display, value read from CAN (WiP)
8. settings 1: Wifi details: SSID + current IP
9. settings 2: date + time formar (12h/24h)
10. settings 3: temperature unit (°C/°F) and pressure unit (bar/psi)
11. settings 4: O2 unit (lambda/AFR)

## Hardware
* NodeMCU ESP8266 ESP-12E board
* SSD1306 OLED screen, 128x32 pixel, I²C interface
* RTC module, DS3231 chip, I²C interface
* CAN bus module, MCP2515 chip, SPI interface
* slim OBD2 female connector
* 1/8 NPT oil pressure sensor, 3 wire, 150psi
* 2x diodes
* optional: 3x micro switches or reuse the OEM ones

## Libraries
* ESP8266, version 2.5.0 tested
* U8G2, version 2.24.3 tested
* MCP_CAN, version 1.5 tested
* DS3231, version 1.0.2 tested
* RingBuf, version 1.0.3 tested
* NTPtimeESP, version 1.0 tested
* SPI
* EEPROM
* SPIFFS
* WiFi
* WebServer
* WiFiManager
* WebServer
* FS
