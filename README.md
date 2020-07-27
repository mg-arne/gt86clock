# Scion FRS / Subaru BRZ / Toyota GT86 Enhanced Clock

## About

## Disclaimer & Background
I'm not a car mechanic nor a software developer. I bought my GT86 with a broken engine and replaced it with a used one. As many other Subaru engines the con rod bearings disintegrate from the lack of lubrication.
Oil temperature and oil pressure seems to be decent indications of the engine health, but unfortunately in stock form there is way to keep an eye on those metrics. That is how this project started.

## Credits
Somebody else had the *ingenious* idea to reuse the clock location. Kudos to her/him!
There are few similar projects out there. I only looked at them very briefly, I enjoyed the challenge to build my own version.

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
