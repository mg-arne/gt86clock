void handleModeButton()
{ 
  // hour button pressed
  if ( digitalRead(buttonPin1) == HIGH && millis()-buttonPin1Pressed < 250 && abs ( buttonPin1Pressed - buttonPin2Pressed ) > 200 )
  {
    if ( modeCurrent == CLOCK && clockRefresh == false )
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
    if ( modeCurrent == CLOCK && clockRefresh == false )
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
    if ( modeCurrent == OILTEMP || modeCurrent == COOLANTTEMP || modeCurrent == OILCOOLANTTEMP  ) //oil+coolant temp
    {
      temperatureCelsius = !temperatureCelsius;
      modeOld = 0; // force refresh
      buttonPin1Pressed=-1; 
      buttonPin2Pressed=-1; 
      writeConfig();
    }
    else if ( modeCurrent == OILPRESSURE ) //oil pressure
    {
      pressureBar = !pressureBar;
      modeOld = 0; // force refresh
      buttonPin1Pressed=-1; 
      buttonPin2Pressed=-1; 
      writeConfig();
    }
    else if ( modeCurrent == CLOCK ) //clock
    {
      syncNTP();
    }
    else if ( modeCurrent == O2 ) //afr + volt
    {
      o2afr = !o2afr;
      modeOld = 0; // force refresh
      buttonPin1Pressed=-1; 
      buttonPin2Pressed=-1; 
      writeConfig();
    }
  }
}
