// Clock
void drawClock(bool updateCompleteDisplay)
{ 
  if ( updateCompleteDisplay == true )
  { 
    u8g2.clearDisplay();
    u8g2.setDrawColor(1);  
    u8g2.drawXBM( 96, 0, iconGTWidth, iconGTHeight, iconGTBits);

    u8g2.setFont(u8g2_font_crox3cb_mf);
   /* if ( clock24h )
    {
        u8g2.drawStr(116,16," ");
        u8g2.drawStr(116,32," ");
    } else {
      if ( clockHour > 12 )
      {
        u8g2.drawStr(113,16,"P");
        clockHour =- 12;
        pm = true;
      } else { 
        u8g2.drawStr(113,16,"A");
        pm = false;
      }
      u8g2.drawStr(113,32,"M");
    }*/
      
    u8g2.setFont(u8g2_font_logisoso32_tn);
    if ( clockHour>9 ) {
      u8g2.drawStr(37-37,32,String(clockHour).c_str());
    } else {
      u8g2.drawStr(37-37,32,"0");
      u8g2.drawStr(57-37,32,String(clockHour).c_str());
    }
    if ( clockMinute>9 ) {
      u8g2.drawStr(84-37,32,String(clockMinute).c_str());
    } else {
      u8g2.drawStr(84-37,32,"0");
      u8g2.drawStr(104-37,32,String(clockMinute).c_str());
    }
    clockRefresh = false;
   
  }  

  u8g2.setDrawColor(drawDots);
  u8g2.drawBox(79-37,8,3,3);
  u8g2.drawBox(79-37,20,3,3);
  u8g2.setDrawColor(1);
  u8g2.sendBuffer(); 
  delay(500);
  drawDots = !drawDots;
}
