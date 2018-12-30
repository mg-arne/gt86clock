// coolant + oil Temp
void drawCoolantOilTemp(bool updateCompleteDisplay)
{ 
  if ( updateCompleteDisplay == true )
  {
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_crox3cb_mf);

    //u8g2.drawStr(2,32,"Oil");
    u8g2.drawXBM( 2, 18, iconOilCanWidth, iconOilCanHeight, iconOilCanBits);
    u8g2.drawXBM( 4, -17, iconCoolantWidth, iconCoolantHeight, iconCoolantBits);

    //u8g2.drawStr(2,16,"Water");

    u8g2.drawCircle(112,18,2);
    u8g2.drawCircle(112,2,2);
    if ( tempC )
    {
      u8g2.drawStr(116,16,"C");
      u8g2.drawStr(116,32,"C");
    } else {
      u8g2.drawStr(116,16,"F");
      u8g2.drawStr(116,32,"F");
    }
  }

  u8g2.setDrawColor(0);
  u8g2.drawBox(70,0,39,32);
  u8g2.setDrawColor(1);
   
  u8g2.setFont(u8g2_font_crox3cb_mf);
   
  if ( coolantTemp > 99 || coolantTemp < -9 ) {
    u8g2.drawStr(69,16,String(coolantTemp).c_str());
  } else if ( coolantTemp < 10 && coolantTemp > -1 ) {
    u8g2.drawStr(95,16,String(coolantTemp).c_str());
  } else {
    u8g2.drawStr(82,16,String(coolantTemp).c_str());
  }

  if ( oilTemp > 99 || oilTemp < -9 ) {
    u8g2.drawStr(69,32,String(oilTemp).c_str());
  } else if ( oilTemp < 10 && oilTemp > -1 ) {
    u8g2.drawStr(95,32,String(oilTemp).c_str());
  } else {
    u8g2.drawStr(82,32,String(oilTemp).c_str());
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
