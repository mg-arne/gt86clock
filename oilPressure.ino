// Oil Pressure
void drawOilPressure(bool updateCompleteDisplay)
{ 
  if ( updateCompleteDisplay == true )
  {
    u8g2.clearDisplay();
    u8g2.drawXBM( 2, 9, iconOilCanWidth, iconOilCanHeight, iconOilCanBits);
 
    u8g2.setFont(u8g2_font_pxplusibmvga9_mf);
    if ( oilPressureBar )
    {
      u8g2.drawStr(120,32,"r");
      u8g2.drawStr(120,21,"a");
      u8g2.drawStr(120,10,"b");
    }
    else
    {
      u8g2.drawStr(120,32,"i");
      u8g2.drawStr(120,21,"s");
      u8g2.drawStr(120,7,"p");
    }
  }
   
  u8g2.setDrawColor(0);
  u8g2.drawBox(60,0,59,32);
  u8g2.setDrawColor(1);
   
  u8g2.setFont(u8g2_font_logisoso32_tn);
  char oilPressureChar[4];
  if ( oilPressureBar )
  {
     dtostrf(oilPressure,1,1,oilPressureChar);
     u8g2.drawStr(65,32,oilPressureChar);
  }
  else
  {
     dtostrf(oilPressure,1,0,oilPressureChar);
     if ( oilPressure > 99 || oilPressure < -9 ) {
       u8g2.drawStr(58,32,oilPressureChar);
     } else if ( oilPressure < 10 && oilPressure > -1 ) {
       u8g2.drawStr(98,32,oilPressureChar);
     } else {
      u8g2.drawStr(78,32,oilPressureChar);
    }
  }
 
  u8g2.sendBuffer();  
  delay(250);
}
