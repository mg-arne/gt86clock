// Oil Temp
void drawOilTemp(bool updateCompleteDisplay)
{ 
  if ( updateCompleteDisplay == true )
  {
    u8g2.clearDisplay();
    u8g2.drawXBM( 2, 9, iconOilCanWidth, iconOilCanHeight, iconOilCanBits);

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
   
  u8g2.setFont(u8g2_font_logisoso32_tr);
   
  if ( oilTemp > 99 || oilTemp < -9 ) {
    u8g2.drawStr(55,32,String(oilTemp).c_str());
  } else if ( oilTemp < 10 && oilTemp > -1 ) {
    u8g2.drawStr(95,32,String(oilTemp).c_str());
  } else {
    u8g2.drawStr(75,32,String(oilTemp).c_str());
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
