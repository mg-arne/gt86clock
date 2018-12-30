// coolant Temp
void drawCoolantTemp(bool updateCompleteDisplay)
{ 
  if ( updateCompleteDisplay == true )
  {
    u8g2.clearDisplay();
    u8g2.drawXBM( 2, 0, iconCoolantWidth, iconCoolantHeight, iconCoolantBits);

    u8g2.setFont(u8g2_font_crox3cb_mf);
    u8g2.drawCircle(118,3,3);
    if ( tempC )
    {
      u8g2.drawStr(116,32,"C");
    } else {
      u8g2.drawStr(116,32,"F");
    }
  }

  u8g2.setDrawColor(0);
  u8g2.drawBox(55,0,60,32);
  u8g2.setDrawColor(1);
   
  u8g2.setFont(u8g2_font_logisoso32_tn);
   
  if ( coolantTemp > 99 || coolantTemp < -9 ) {
    u8g2.drawStr(55,32,String(coolantTemp).c_str());
  } else if ( coolantTemp < 10 && coolantTemp > -1 ) {
    u8g2.drawStr(95,32,String(coolantTemp).c_str());
  } else {
    u8g2.drawStr(75,32,String(coolantTemp).c_str());
  }
  
  if ( millis() - lastTempUpdate < 10*1000 ) // no dot, if we have resent data
  {
     u8g2.setDrawColor(0); 
     u8g2.drawCircle(69,31,1);
     u8g2.setDrawColor(1);  
  }
  else
  {
     u8g2.drawCircle(69,31,1);
  }
  
  u8g2.sendBuffer();  
}
