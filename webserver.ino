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
    if (SPIFFS.exists(pathWithGz)) {
      path += ".gz";
    }
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
  } else if (filename.endsWith(".htm")) {
    return "text/html";
  } else if (filename.endsWith(".html")) {
    return "text/html";
  } else if (filename.endsWith(".css")) {
    return "text/css";
  } else if (filename.endsWith(".js")) {
    return "application/javascript";
  } else if (filename.endsWith(".png")) {
    return "image/png";
  } else if (filename.endsWith(".gif")) {
    return "image/gif";
  } else if (filename.endsWith(".jpg")) {
    return "image/jpeg";
  } else if (filename.endsWith(".ico")) {
    return "image/x-icon";
  } else if (filename.endsWith(".xml")) {
    return "text/xml";
  } else if (filename.endsWith(".pdf")) {
    return "application/x-pdf";
  } else if (filename.endsWith(".zip")) {
    return "application/x-zip";
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

void handleSpecificArg() { 
  if ( server.arg("mode") == "0" || server.arg("mode") == "1" || server.arg("mode") == "2" || server.arg("mode") == "3" || server.arg("mode") == "4" || server.arg("mode") == "5" || server.arg("mode") == "6" || server.arg("mode") == "7" ){ 
    modeCurrent = server.arg("mode").toInt();                                
  }
  if ( server.arg("clock24h") == "false" || server.arg("clock24h") == "true"  ){     
    clock24h = server.arg("clock24h");
    modeOld = 0;    
  }
  if ( server.arg("pressureBar") == "false" || server.arg("pressureBar") == "true"  ){     
    pressureBar = server.arg("pressureBar");   
    modeOld = 0;    
  }
  if ( server.arg("temperatureCelsius") == "false" || server.arg("temperatureCelsius") == "true"  ){     
    temperatureCelsius = server.arg("temperatureCelsius"); 
    modeOld = 0;    
  }
  if ( server.arg("afrLambda") == "false" || server.arg("afrLambda") == "true"  ){     
    afrLambda = server.arg("afrLambda");
    modeOld = 0;    
  }
  if ( server.arg("ntp") == "true" ){     
    syncNTP();
    modeOld = 0;    
  }
  
  handleFileRead("/");
}
