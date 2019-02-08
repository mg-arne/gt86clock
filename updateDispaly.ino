void updateDisplay(void * parameter) {
  while (1) {
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
    case 0:
      drawLogo(updateCompleteDisplay);
      break;
    case 1:
      drawOilTemp(updateCompleteDisplay);
      break;
    case 2:
      drawCoolantTemp(updateCompleteDisplay);
      break;
    case 3:
      drawCoolantOilTemp(updateCompleteDisplay);
      break;
    case 4:
      drawOilPressure(updateCompleteDisplay);
      break;
    case 5:
      drawClock(updateCompleteDisplay);
      break;
    case 6:
      drawAfrAndVoltage(updateCompleteDisplay);
      break;
    case 7:
      drawSettings(updateCompleteDisplay);
      break;
    default:
      drawLogo(updateCompleteDisplay);
    }

    readyForModeChange = true;
  }
}
