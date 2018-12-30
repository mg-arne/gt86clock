// LOGO
void drawLogo(bool updateCompleteDisplay)
{   
   if ( updateCompleteDisplay == true )
   {  
     u8g2.clearDisplay();  
     u8g2.drawXBM( 0, 0, logoWidth, logoheight, logoBits);
     u8g2.sendBuffer(); 
     delay(1000);
     modeCurrent=5;
   }
}
