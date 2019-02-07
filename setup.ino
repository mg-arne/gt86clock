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

  if(CAN0.begin(MCP_STDEXT, CAN_500KBPS, MCP_8MHZ) == CAN_OK)
  {
    Serial.println("Can1 MCP2515 Initialized Successfully!");
    delay(500);
  } else {
    Serial.println("Error Initializing MCP2515...");
    delay(4000);
  }

  xTaskCreatePinnedToCore(updateDisplay, "updateDisplay", 4096, NULL, 1, NULL, ARDUINO_RUNNING_CORE);

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

  WiFiManager wifiManager;
  wifiManager.autoConnect("gt86clock");

  server.begin();
  
  server.on("/", handleSpecificArg);   
  server.on("/date.json", handleDateJson);
  server.on("/temperature.json", handleTemperatureJson);

  SPIFFS.begin();
  
  server.onNotFound([]() {
    if (!handleFileRead(server.uri())) {
      server.send(404, "text/plain", "FileNotFound");
    }
  });
}
