#include <U8g2lib.h> 

#ifdef U8X8_HAVE_HW_I2C 
  #include <Wire.h> 
#endif 
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE, /* clock=*/ SCL, /* data=*/ SDA);

#include <mcp_can.h>  
#include <SPI.h>   
#define CAN0_INT 16           // Set Interupt zu pin D2
MCP_CAN CAN0(15);             // Set CS to pin 15 (D8 on my NodeMCU)

#include <EEPROM.h>
#include "DS3231.h"

#include <base64.h>

RTClib RTC;
DS3231 Clock;

#include "logos.h"

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
ESP8266WebServer server(80);

WiFiManager wifiManager;

#include <FS.h>

#include <NTPtimeESP.h>
NTPtime NTPch("ch.pool.ntp.org");
DateTime now;
strDateTime dateTime;

#define MAXSCREENS 10
#define LOGO 0
#define CLOCK 1
#define OILTEMP 2
#define COOLANTTEMP 3
#define OILCOOLANTTEMP 4
#define OILPRESSURE 5
#define O2 6
#define SETTINGSWIFI 7
#define SETTINGSCLOCK 8
#define SETTINGSUNITS 9
#define SETTINGSO2 10


int buttonPin1=2;
int buttonPin2=0;
int buttonPin1Pressed=-1;     // whether the button input 1 is pressed
int buttonPin2Pressed=-1;     // whether the button input 2 is pressed
int clockHour=8;
int clockMinute=30;
int coolantTemp=0;
int modeCurrent=0;
int modeOld=-1;
int modeSaved=-1;
int oilTemp=0;
int lastModeChange=0;
int lastTempUpdate=0;
int lastJsonAppend=0;

long unsigned int rxId;

bool o2afr=true;
bool clockRefresh=false;
bool clock24h=true;            //true=24h, false=12h
bool pm;                       //true=pm, false=am
bool drawDots=false;
bool pressureBar=true;         //true=Bar, false=Psi
bool temperatureCelsius=true;  //true=Celsius, false=Fahrenheit
bool readyForModeChange=true;
bool updateCompleteDisplay=true;

float afr=14.6;
float voltage=0;
float oilPressure;
float oilPressureOld;
float oilPressureOffset=114;
float oilPressureScalingFactor=0.172018348623853; 

String jsonFile;

unsigned char len = 0;
unsigned char buf[12];
