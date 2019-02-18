void loop(void) { 

  handleModeButton();

  now = RTC.now();
  server.handleClient(); //Handling of incoming requests
  wifiManager.process();
  
  // update oil temp test values
  if(CAN_MSGAVAIL == CAN0.checkReceive())            
  {
    CAN0.readMsgBuf(&rxId, &len, buf);        

    if ( rxId == 0x360 )
    {
      oilTemp     = buf[2]-40; 
      coolantTemp = buf[3]-40;              
               
      if ( ! temperatureCelsius )
      {
        oilTemp=round(oilTemp*1.8+32);
        coolantTemp=round(coolantTemp*1.8+32);
      }

      lastTempUpdate=millis();
    }  else if ( rxId = 0x134 )
    {
      // value = ((strtol(&buf[6],0,16)*256)+strtol(&buf[9],0,16))/32768*14.7;  //(A*256+B)/32768*14.7

      //afr = buf[0];   
      
      if ( o2afr )
      {
        if ( afr < -40 || afr > 320 )
          afr=999;
      } else {
        afr=float(round((afr/14.7)*100))/100;
      
      if ( afr < -0.2 || afr > 2 )
        afr=-1;
      }     
    }
    else if ( rxId = 0x142 )
    {
      voltage = (buf[3]*256+buf[4])/1000; //aka ((A*256)+B)/1000 ;      
      voltage = float(round(voltage*10))/10;
      if ( voltage < 5 || voltage > 16 ) voltage=-1; 
    } 
    
    if ( coolantTemp < -39 || coolantTemp > 320 ) { coolantTemp=0; }
  }

  oilPressureOld=analogRead(A0);
  if ( oilPressureOld < oilPressureOffset ) { oilPressureOld = oilPressureOffset; }
  //get the value and scale it
  oilPressure=float((oilPressureOld-oilPressureOffset)*oilPressureScalingFactor);
  if ( pressureBar )
  {
    oilPressure=oilPressure*0.0689476;
    oilPressure=float(round(oilPressure*10))/10;
    //cap it at 9.9 bar
    if ( oilPressure >= 10 ) { oilPressure=9.9; }
  }
  else
  {
    oilPressure=round(oilPressure);
    //cap it at 150 psi
    if ( oilPressure > 150 ) { oilPressure=150; }
  }  

  if ( modeCurrent == CLOCK && ( clockHour != now.hour() || clockMinute != now.minute() ) )
  {
    clockHour = now.hour();
    clockMinute = now.minute();
    if ( clockHour > 24 && clockMinute > 0)
    {
      clockHour=0;
      Clock.setHour(clockHour);
    }
    if ( clockMinute > 60 )
    {
      clockMinute=0;
      Clock.setMinute(clockMinute);
    }
    clockRefresh = true; 
  }

  // no dot, if we have recent data
  if ( millis() - lastTempUpdate < 10*1000 )
  {
    u8g2.setDrawColor(0); 
    u8g2.drawCircle(1,1,1);
    u8g2.setDrawColor(1);  
  }
  else
    u8g2.drawCircle(1,1,1);
    
  // check for complete refresh or just updated values
  if ( modeOld != modeCurrent || clockRefresh == true )
  {
    updateCompleteDisplay = true;
    modeOld = modeCurrent; 
  } else
    updateCompleteDisplay = false;  

  // refresh display
  switch (modeCurrent) {
    case LOGO:
      drawLogo(updateCompleteDisplay);
      break;
    case CLOCK:
      drawClock(updateCompleteDisplay);
      break;
    case OILTEMP:
      drawOilTemp(updateCompleteDisplay);
      break;
    case COOLANTTEMP:
       drawCoolantTemp(updateCompleteDisplay);
      break;
    case OILCOOLANTTEMP:
      drawCoolantOilTemp(updateCompleteDisplay);
      break;
    case OILPRESSURE:
      drawOilPressure(updateCompleteDisplay);
      break;
    case O2:
      drawAfrAndVoltage(updateCompleteDisplay);
      break;
    case SETTINGS:
      drawSettingsWifi(updateCompleteDisplay);
      break;
    case 8:
      drawSettingsClock(updateCompleteDisplay);
      break;
    case 9:
      drawSettingsUnits(updateCompleteDisplay);
      break;
    case 10:
      drawSettingsO2(updateCompleteDisplay);
      break;
    default:
      drawLogo(updateCompleteDisplay);
  }

  if ( millis() - lastJsonAppend > 10000 ) {
    appendJsonFile(jsonFile);
    lastJsonAppend =  millis();  
  }

  readyForModeChange = true;
}

void customDelay(int reqDelay) {
  for (int i=reqDelay;i>=0;i-=50) {
    server.handleClient(); //Handling of incoming requests
    if ( modeOld != modeCurrent )
      break; 
    delay(50);
  }
}
