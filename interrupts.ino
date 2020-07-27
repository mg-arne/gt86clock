void ICACHE_RAM_ATTR handleInterruptPin1() {
  if ( digitalRead(buttonPin1) == LOW )
    buttonPin1Pressed=millis();
    
  handleModeButton();
}

void ICACHE_RAM_ATTR handleInterruptPin2() {
  if ( digitalRead(buttonPin2) == LOW )
    buttonPin2Pressed=millis();
    
  handleModeButton();
}
