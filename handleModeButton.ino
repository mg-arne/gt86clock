void handleModeButton()
{ 
  // hour button pressed
  if ( digitalRead(buttonPin1) == HIGH && millis()-buttonPin1Pressed < 250 && abs ( buttonPin1Pressed - buttonPin2Pressed ) > 200 )
  {
    if ( modeCurrent == 5 && clockRefresh == false )
    { 
     // buttonHourPressed=0;
      clockHour++;
      clockHour = clockHour % 24;
      Clock.setHour(clockHour);
      clockRefresh = true; 
    }
    buttonPin1Pressed=-1; 
  }

  // minute button pressed
  if ( digitalRead(buttonPin2) == HIGH && millis()-buttonPin2Pressed < 250 && abs ( buttonPin1Pressed - buttonPin2Pressed ) > 200 )
  {
    if ( modeCurrent == 5 && clockRefresh == false )
    { 
     // buttonMinutePressed=0;
      clockMinute++;
      clockMinute = clockMinute % 60;
      Clock.setMinute(clockMinute);
      Clock.setSecond(0);
      clockRefresh = true; 
    } 
    buttonPin2Pressed=-1; 
  }

  // mode button, short press
  if ( buttonPin1Pressed != -1 && buttonPin2Pressed != -1 && digitalRead(buttonPin1) == HIGH && digitalRead(buttonPin2) == HIGH && millis() - buttonPin2Pressed > 50 && millis() - buttonPin2Pressed > 50 && abs ( buttonPin1Pressed - buttonPin2Pressed ) < 200 && millis() - buttonPin2Pressed < 250 && readyForModeChange && millis() - lastModeChange > 500 )
  {    
    readyForModeChange = false;
    modeCurrent++;
    // there is only mode 0-6 availble, logo only on start
    if ( modeCurrent > MAXSCREENS-3 )
      modeCurrent = 1;
        
    buttonPin1Pressed=-1; 
    buttonPin2Pressed=-1; 
    lastModeChange = millis();
  }

  // mode button, long press
  if ( buttonPin1Pressed != -1 && buttonPin2Pressed != -1 && digitalRead(buttonPin1) == LOW && digitalRead(buttonPin2) == LOW && abs ( buttonPin1Pressed - buttonPin2Pressed ) < 200 && millis() - buttonPin2Pressed > 1000 && millis() - buttonPin2Pressed < 5000 )
  {
    if ( modeCurrent == 1 || modeCurrent == 2 || modeCurrent == 3  ) //oil+coolant temp
    {
      temperatureCelsius = !temperatureCelsius;
      modeOld = 0; // force refresh
      buttonPin1Pressed=-1; 
      buttonPin2Pressed=-1; 
      EEPROM.put(0, temperatureCelsius);
      EEPROM.commit();
    }
    else if ( modeCurrent == 4 ) //oil pressure
    {
      pressureBar = !pressureBar;
      modeOld = 0; // force refresh
      buttonPin1Pressed=-1; 
      buttonPin2Pressed=-1; 
      EEPROM.put(1, pressureBar);
      EEPROM.commit();
    }
    else if ( modeCurrent == 5 ) //clock
    {
      /*clock24h = !clock24h;
      if ( clock24h && pm )
        clockHour+=12;
      else
        clockHour-=12;
        
      Clock.setHour(clockHour);
      clockRefresh = true;
      buttonPin1Pressed=-1; 
      buttonPin2Pressed=-1; 
      EEPROM.put(2, clock24h);
      EEPROM.commit();*/
      syncNTP();
    }
    else if ( modeCurrent == 6 ) //afr + volt
    {
      o2afr = !o2afr;
      modeOld = 0; // force refresh
      buttonPin1Pressed=-1; 
      buttonPin2Pressed=-1; 
      EEPROM.put(3, o2afr);
      EEPROM.commit();
    }
  }
}
