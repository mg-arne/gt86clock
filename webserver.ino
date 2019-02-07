void handleDateJson() { //Handler for the body path
  char temp[75];
  String message;
  sprintf(temp, "dataDateJson = '[{ \"date\": \"%d-%02d-%02d %02d:%02d:%02d\" }]';", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second() );
  message += temp;
 
  server.send(200, "application/json", message);
}

void handleTemperatureJson() { //Handler for the body path
  char temp[75];
  String message;
 
 //for (uint8_t j = 0; j < myBuffer.size(); j++) {
 //   Serial.println(myBuffer[j]);
 // }
 //sprintf(temp, "dataDateJson = '[{ \"date\": \"%d-%02d-%02d %02d:%02d:%02d\" }]';", now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second() );
 //message += temp;
 
 server.send(200, "application/json", message);
}

bool handleFileRead(String path) {
  Serial.println("handleFileRead: " + path);
  if (path.endsWith("/")) {
    path += "index.html";
  }
  String contentType = getContentType(path);
  String pathWithGz = path + ".gz";
  if (SPIFFS.exists(pathWithGz) || SPIFFS.exists(path)) {
    if (SPIFFS.exists(pathWithGz))
      path += ".gz";
    File file = SPIFFS.open(path, "r");
    server.streamFile(file, contentType);
    file.close();
    return true;
  }
  return false;
}

String getContentType(String filename) {
  if (server.hasArg("download")) {
    return "application/octet-stream";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".gz")) {
    return "application/x-gzip";
  }
  return "text/plain";
}

void syncNTP()
{
  dateTime = NTPch.getNTPtime(1.0, 1);
  if(dateTime.valid){
    NTPch.printDateTime(dateTime);
    
    Clock.setHour(dateTime.hour);
    Clock.setMinute(dateTime.minute);
    Clock.setSecond(dateTime.second);
    Clock.setYear(dateTime.year-2000);
    Clock.setMonth(dateTime.month);
    Clock.setDate(dateTime.day);
  }
}

boolean setIfBool(String varName) {
  if ( server.arg(varName) == "false" || server.arg(varName) == "true"  ) {     
    modeOld = 0; 
    return server.arg(varName);
  }
}

void handleSpecificArg() { 
  if ( isDigit(server.arg("mode").charAt(0)) && server.arg("mode").toInt() >= 1 && server.arg("mode").toInt() <= 7 )
    modeCurrent = server.arg("mode").toInt();                                
  
  clock24h           = setIfBool("clock24h");
  pressureBar        = setIfBool("pressureBar");
  temperatureCelsius = setIfBool("temperatureCelsius");
  o2afr              = setIfBool("o2afr");

  if ( server.arg("ntp") == "true" ) {     
    syncNTP();
    modeOld = 0;    
  }
  
  handleFileRead("/");
}
