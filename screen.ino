void drawAfrAndVoltage(bool updateCompleteDisplay)
{ 
  if ( o2afr )
  {
    char afrChar[4];
    dtostrf(afr,1,1,afrChar);
    char voltageChar[4];
    
    dtostrf(voltage,1,1,voltageChar);
    drawTwoValues(o2Width     , o2Height     , o2Bits     , afrChar    , countDigits(afr), "" , 
                  batteryWidth, batteryHeight, batteryBits, voltageChar, 4               , "V", updateCompleteDisplay);
  }
  else
  {
    char afrChar[4];
    dtostrf(afr,1,2,afrChar);
    char voltageChar[4];
    dtostrf(voltage,1,1,voltageChar);
    
    drawTwoValues(o2Width     , o2Height     , o2Bits     , afrChar    , countDigits(afr*1.8+32), "" , 
                  batteryWidth, batteryHeight, batteryBits, voltageChar, 4                      , "V", updateCompleteDisplay);
  }
}

void drawCoolantOilTemp(bool updateCompleteDisplay)
{ 
  if ( temperatureCelsius )
    drawTwoValues(iconCoolantWidth, iconCoolantHeight, iconCoolantBits, (char*)String(coolantTemp).c_str(), countDigits(coolantTemp) , "C", 
                  iconOilCanWidth , iconOilCanHeight , iconOilCanBits , (char*)String(oilTemp).c_str()    , countDigits(oilTemp)     , "C", updateCompleteDisplay);
  else
    drawTwoValues(iconCoolantWidth, iconCoolantHeight, iconCoolantBits, (char*)String(coolantTemp*1.8+32).c_str(), countDigits(coolantTemp*1.8+32) , "F", 
                  iconOilCanWidth , iconOilCanHeight , iconOilCanBits , (char*)String(oilTemp*1.8+32).c_str()    , countDigits(oilTemp*1.8+32)     , "F", updateCompleteDisplay);
}

void drawCoolantTemp(bool updateCompleteDisplay)
{ 
   if ( temperatureCelsius )
     drawSingleValue(iconCoolantWidth, iconCoolantHeight, iconCoolantBits, (char*)String(coolantTemp).c_str()   , countDigits(coolantTemp)       , "C", updateCompleteDisplay);
   else
     drawSingleValue(iconCoolantWidth, iconCoolantHeight, iconCoolantBits, (char*)String(oilTemp*1.8+32).c_str(), countDigits(coolantTemp*1.8+32), "F", updateCompleteDisplay);
}

void drawOilTemp(bool updateCompleteDisplay)
{ 
   if ( temperatureCelsius )
     drawSingleValue(iconOilCanWidth, iconOilCanHeight, iconOilCanBits, (char*)String(oilTemp).c_str()       , countDigits(oilTemp)       , "C", updateCompleteDisplay);
   else
     drawSingleValue(iconOilCanWidth, iconOilCanHeight, iconOilCanBits, (char*)String(oilTemp*1.8+32).c_str(), countDigits(oilTemp*1.8+32), "F", updateCompleteDisplay);
}

void drawOilPressure(bool updateCompleteDisplay)
{ 
   if ( pressureBar )
   {
     char oilPressureChar[4];
     dtostrf(oilPressure,1,1,oilPressureChar);
     drawSingleValue(iconOilCanWidth, iconOilCanHeight, iconOilCanBits, oilPressureChar, 3, "bar", updateCompleteDisplay);
   }
   else
   { 
     char oilPressureChar[4];
     dtostrf(oilPressure,1,0,oilPressureChar);
     drawSingleValue(iconOilCanWidth, iconOilCanHeight, iconOilCanBits, oilPressureChar, 2, "psi", updateCompleteDisplay);
   }

  customDelay(250);
}

void drawLogo(bool updateCompleteDisplay)
{   
   if ( updateCompleteDisplay == true )
   {
     u8g2.clearDisplay();  
     u8g2.drawXBM( 0, 0, logoWidth, logoHeight, logoBits);
     u8g2.sendBuffer(); 
     modeCurrent=5;
     modeOld=5;
     customDelay(3000);
   }
}

int countDigits(int n) 
{ 
  if ( n < 0 )
    return floor(log10(abs(n))+2);
  else if ( n > 0 )
    return floor(log10(abs(n))+1); 
  else  
    return 1;
} 

void drawSingleValue(int iconWidth, int iconHeight, unsigned char iconBits[], char value[4], int valueLength, char unit[3], bool updateCompleteDisplay)
{ 
  if ( updateCompleteDisplay == true )
  {
    u8g2.clearDisplay();
    u8g2.drawXBM( 2, round((32-iconHeight)/2), iconWidth, iconHeight, iconBits);

    if ( unit == "C" || unit == "F" )
    {
      u8g2.drawCircle(118,3,3);
      u8g2.setFont(u8g2_font_crox3cb_mf);
      u8g2.drawStr(116,32,unit);
    }
    else
    {
      u8g2.setFont(u8g2_font_pxplusibmvga9_mf);
      u8g2.drawStr(120,32,&unit[2]);
      u8g2.drawStr(120,21,&unit[1]);
      u8g2.drawStr(120,10,&unit[0]);
    }
  }

  u8g2.setDrawColor(0);
  u8g2.drawBox(55,0,60,32);
  u8g2.setDrawColor(1);
   
  u8g2.setFont(u8g2_font_logisoso32_tn);
  u8g2.drawStr(115-valueLength*20,32,value);

  u8g2.sendBuffer();  
}

void drawTwoValues(int iconUpWidth, int iconUpHeight, unsigned char iconUpBits[], char valueUp[4], int valueUpLength, char unitUp[3], int iconDownWidth, int iconDownHeight, unsigned char iconDownBits[], char valueDown[4], int valueDownLength, char unitDown[3], bool updateCompleteDisplay)
{ 
  if ( updateCompleteDisplay == true )
  {
    u8g2.clearDisplay();
    u8g2.drawXBM( 4, -17, iconUpWidth  , iconUpHeight  , iconUpBits );
    u8g2.drawXBM( 2,  18, iconDownWidth, iconDownHeight, iconDownBits);
    
    if ( unitUp == "C" || unitDown == "F" )
    {
      u8g2.setFont(u8g2_font_crox3cb_mf);
      u8g2.drawCircle(112,18,2);
      u8g2.drawCircle(112,2,2);
      u8g2.drawStr(116,16,unitUp);
      u8g2.drawStr(116,32,unitDown);
    }
    else if ( unitDown == "V" ) {
      u8g2.setFont(u8g2_font_crox3cb_mf);
      u8g2.drawStr(116,32,unitDown);
    }
  }

  u8g2.setDrawColor(0);
  u8g2.drawBox(70,0,39,32);
  u8g2.setDrawColor(1);
   
  u8g2.setFont(u8g2_font_crox3cb_mf);
   
  u8g2.drawStr(108-valueUpLength*13,16,valueUp);
  u8g2.drawStr(108-valueDownLength*13,32,valueDown);

  u8g2.sendBuffer();  
}
