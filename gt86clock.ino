#if CONFIG_FREERTOS_UNICORE
  #define ARDUINO_RUNNING_CORE 0
#else
  #define ARDUINO_RUNNING_CORE 1
#endif

#include <U8g2lib.h> 
#ifdef U8X8_HAVE_HW_I2C 
  #include <Wire.h> 
#endif 
U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ SCL, /* data=*/ SDA, /* reset=*/ U8X8_PIN_NONE);

#include <mcp_can.h>  
#include <SPI.h>   
#define CAN0_INT 16           // Set Interupt zu pin D2
MCP_CAN CAN0(15);             // Set CS to pin 15 (D8 on my NodeMCU)

#include <EEPROM.h>
#include "DS3231.h"
#include "SPIFFS.h"

#include <base64.h>

RTClib RTC;
DS3231 Clock;

#include "logos.h"

#include <WiFi.h>
#include <WebServer.h>
#include <WiFiManager.h>
WebServer server(80);

#include <FS.h>

#include <RingBuf.h>
RingBuf<int8_t, 240> coolantBuffer;
RingBuf<int8_t, 240> oilBuffer;

#include <NTPtimeESP.h>
NTPtime NTPch("ch.pool.ntp.org");
DateTime now;
strDateTime dateTime;

int buttonPin1=2;
int buttonPin2=0;
int buttonPin1Pressed=-1;     // whether the button input 1 is pressed
int buttonPin2Pressed=-1;     // whether the button input 2 is pressed
int clockHour=8;
int clockMinute=30;
int coolantTemp;
int modeCurrent=0;
int modeOld=-1;
int oilTemp;
int lastModeChange=0;
int lastTempUpdate=0;

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
float voltage=-1;
float oilPressure;
float oilPressureOld;
float oilPressureOffset=114;
float oilPressureScalingFactor=0.172018348623853; 

unsigned char len = 0;
unsigned char buf[12];
