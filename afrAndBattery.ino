// coolant + oil Temp
void drawAfrAndBat(bool updateCompleteDisplay)
{ 
  if ( updateCompleteDisplay == true )
  {
    u8g2.clearDisplay();
    u8g2.setFont(u8g2_font_crox3cb_mf);

    u8g2.drawStr(2,32,"Bat.");

    if ( afrLambda )
    {
      u8g2.drawStr(2,16,"AFR");
    } else {
      u8g2.drawStr(2,16,"Lam.");
    }
    
    u8g2.drawStr(116,32,"V");
  }

  u8g2.setDrawColor(0);
  u8g2.drawBox(70,0,39,32);
  u8g2.setDrawColor(1);
   
  u8g2.setFont(u8g2_font_crox3cb_mf);

  if ( afrLambda )
  {
    char afrChar[4];
    dtostrf(afr,1,1,afrChar);
    u8g2.drawStr(62,16,afrChar);
  } else {
    char afrChar[4];
    dtostrf(afr,1,2,afrChar);
    u8g2.drawStr(75,16,afrChar);
  }
  char batChar[4];
  dtostrf(bat,1,1,batChar);
  u8g2.drawStr(62,32,batChar);
  
  u8g2.sendBuffer();  
}
