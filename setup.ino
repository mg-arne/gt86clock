void setup(void) {   
  u8g2.begin();// Oled display begins  
  u8g2.setFlipMode(1);

  Wire.begin();

  Serial.begin(115200);
   
  pinMode(A0,           INPUT);         // oil pressure
  pinMode(buttonPin1,   INPUT_PULLUP);  // muxed for the 3 buttons
  pinMode(buttonPin2,   INPUT_PULLUP);  // muxed for the 3 buttons

  // falling = down = pressed
  // rising  = up   = release
  attachInterrupt(digitalPinToInterrupt(buttonPin1), handleInterruptPin1, CHANGE); 
  attachInterrupt(digitalPinToInterrupt(buttonPin2), handleInterruptPin2, CHANGE); 
 
  EEPROM.begin(512);
  readConfig();

  if(CAN0.begin(MCP_STDEXT, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
  {
    Serial.println("Can1 MCP2515 Initialized Successfully!");
    customDelay(500);
  } else {
    Serial.println("Error Initializing MCP2515...");
    customDelay(4000);
  }

 // Can Hardware Filter  
  CAN0.init_Mask(0,0,0x07FF0000);                
  CAN0.init_Filt(0,0,0x07DF0000);                
  CAN0.init_Filt(1,0,0x07DF0000);                 

  CAN0.init_Mask(1,0,0x07FF0000);                
  CAN0.init_Filt(2,0,0x07E80000);        // OBD
  CAN0.init_Filt(3,0,0x03600000);        // Water / Oil
  CAN0.init_Filt(4,0,0x01340000);        // AFR
  CAN0.init_Filt(5,0,0x01420000);        // Voltage

  CAN0.setMode(MCP_NORMAL);

  wifi_station_set_hostname("gt86clock");

  WiFiManager wifiManager;
  wifiManager.autoConnect("gt86clock");
  WiFi.hostname("gt86clock");

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
  File file = SPIFFS.open(jsonFile, "a");

  if(!file){
    Serial.println("There was an error opening the file for appending");
    return false;
  }

  char temp[75];
  String message;
  sprintf(temp, ",{\"%d\":[\"%d\",\"%d\",\"%d\",\"%d\",\"%d\"]}", millis(),oilTemp,coolantTemp,oilPressure,o2afr,voltage);
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
}

void writeConfig(){
  EEPROM.put(0, temperatureCelsius);
  EEPROM.put(1, pressureBar);
  EEPROM.put(2, clock24h);
  EEPROM.put(3, o2afr);
  EEPROM.commit();  
}
