void setup(void) { \  
  u8g2.begin();// Oled display begins  
  u8g2.setFlipMode(1);

  Wire.begin();

  Serial.begin(115200);
  
  Serial.println("Serial OK");
   
  pinMode(A0,           INPUT);         // oil pressure
  pinMode(buttonPin1,   INPUT_PULLUP);  // muxed for the 3 buttons
  pinMode(buttonPin2,   INPUT_PULLUP);  // muxed for the 3 buttons

  Serial.println("PINS1 ok");

  // falling = down = pressed
  // rising  = up   = release
  attachInterrupt(digitalPinToInterrupt(buttonPin1), handleInterruptPin1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(buttonPin2), handleInterruptPin2, CHANGE); 

  Serial.println("PINS2 ok");
 
  EEPROM.begin(512);
  readConfig();

   Serial.println("EEPROM ok");

  if(CAN0.begin(MCP_STDEXT, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
  {
    Serial.println("Can1 MCP2515 Initialized Successfully!");
    customDelay(500);
  } else {
    Serial.println("Error Initializing MCP2515...");
    customDelay(4000);
  }

   Serial.println("CAN ok");

 // Can Hardware Filter  
  CAN0.init_Mask(0,0,0x0FF0000);                
  CAN0.init_Filt(0,0,0x07DF0000);                
  CAN0.init_Filt(1,0,0x07DF0000);                 

  CAN0.init_Mask(1,0,0x07FF0000);                
  CAN0.init_Filt(2,0,0x07E80000);        // OBD
  CAN0.init_Filt(3,0,0x03600000);        // Water / Oil
  CAN0.init_Filt(4,0,0x01340000);        // AFR
  CAN0.init_Filt(5,0,0x01420000);        // Voltage

  CAN0.setMode(MCP_NORMAL);

  wifi_station_set_hostname("gt86clock");

  wifiManager.setConnectTimeout(5);
  wifiManager.setConfigPortalBlocking(false);

  Serial.println("WIFI ok");
  
  SPIFFS.begin();
  
  server.begin();
  server.on("/config", handleSpecificArg);   
  server.on("/json.js", handleJson);   
  server.on("/date.js", handleDateJs);
  server.on("/config.js", handleConfigJs);
  server.on("/temperature.js", handleTemperatureJs);
  server.onNotFound([]() {
    if (!handleFileRead(server.uri()))
      server.send(404, "text/plain", "FileNotFound");
  });

  now = RTC.now();
  char temp[75];
  sprintf(temp, "/json/gt86clock_%04d%02d%02d%02d%02d.js", now.year(),now.month(),now.day(),now.hour(),now.minute());
  jsonFile += temp;
  createJsonFile(jsonFile);
}

bool createJsonFile(String jsonFile) {
  File file = SPIFFS.open(jsonFile, "w");
  
  if(!file){
    Serial.println("There was an error creating a new json file");
    return false;
  }
 
  if(!file.println("{\"Time\":[\"Oil Temperature\",\"Coolant Temperature\",\"Oil Pressure\",\"O2\",\"Voltage\"]}")) {
    Serial.println("File append failed");
    return false;
  }
    
  file.close();
  return true;
}

bool appendJsonFile(String jsonFile) { 

  FSInfo fs_info;
  SPIFFS.info(fs_info);
  if ( ( fs_info.totalBytes - fs_info.usedBytes ) < 50 ) {
     Dir dir = SPIFFS.openDir("/json");
     if (dir.next())
       SPIFFS.remove("/json/"+dir.fileName());
     Serial.println("Removing /json/"+dir.fileName()+". SPIFFS is too full.");
  }
  
  File file = SPIFFS.open(jsonFile, "a");

  if(!file){
    Serial.println("There was an error opening the file for appending");
    return false;
  }

  char temp[75];
  String message;
  sprintf(temp, ",{\"%d\":[\"%d\",\"%d\",\"%.2f\",\"%.2f\",\"%.1f\"]}", millis(),oilTemp,coolantTemp,oilPressure,afr,voltage);
  message += temp;
 
  if(!file.println(message)) {
    Serial.println("File append failed");
    return false;
  }
  
  file.close();
  return true;
}
  
void readConfig(){
  byte tmp;
  int addr=0;
  EEPROM.get(addr,tmp);
  temperatureCelsius = bitRead(tmp,0);
  addr++;
  EEPROM.get(addr,tmp);
  pressureBar = bitRead(tmp,0);
  addr++;
  EEPROM.get(addr,tmp);
  clock24h = bitRead(tmp,0);
  addr++;
  EEPROM.get(addr,tmp);
  o2afr = bitRead(tmp,0);
  addr++;
  modeSaved = eepromReadInt(addr);
  if ( modeSaved < CLOCK || modeSaved > MAXSCREENS-3 )
      modeSaved = CLOCK;
}

void writeConfig(){
  EEPROM.put(0, temperatureCelsius);
  EEPROM.put(1, pressureBar);
  EEPROM.put(2, clock24h);
  EEPROM.put(3, o2afr);
  eepromWriteInt(4, modeCurrent);
  EEPROM.commit();  
}

int eepromReadInt(int adr) {
byte low, high;
  low=EEPROM.read(adr);
  high=EEPROM.read(adr+1);
  return low + ((high << 8)&0xFF00);
}

void eepromWriteInt(int adr, int wert) {
byte low, high;
  low=wert&0xFF;
  high=(wert>>8)&0xFF;
  EEPROM.write(adr, low); 
  EEPROM.write(adr+1, high);
  return;
}
