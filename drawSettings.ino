// Settings
void drawSettings(bool updateCompleteDisplay)
{   
   if ( updateCompleteDisplay == true )
   {  
     u8g2.clearDisplay();  
     u8g2.setDrawColor(1);
     u8g2.setFont(u8g2_font_crox2tb_tf);

     String ipaddress = WiFi.localIP().toString();
     u8g2.drawStr(1,16,("SSID:"+WiFi.SSID()).c_str()); 
     u8g2.drawStr(1,32,ipaddress.c_str());
     u8g2.sendBuffer(); 
     delay(3000);

     char temp[50];
     u8g2.clearDisplay();  
     sprintf(temp, "%d-%02d-%02d %02d:%02d:%02d"  , now.year(), now.month(), now.day(), now.hour(), now.minute(), now.second());
     u8g2.drawStr(1,16, temp); 
     u8g2.drawStr(1,32,"CLOCK: 24h");      
     u8g2.sendBuffer(); 
     delay(2000);  
     
     u8g2.clearDisplay();  
     u8g2.drawStr(1,16,"TEMP.: C"); 
     u8g2.drawStr(1,32,"PRESSURE: bar");
     u8g2.sendBuffer(); 
     delay(2000);
          
     u8g2.clearDisplay();  
     u8g2.drawStr(1,16,"AirFuelRatio: AFR");
     u8g2.sendBuffer(); 
     delay(2000);
      
   }
}
