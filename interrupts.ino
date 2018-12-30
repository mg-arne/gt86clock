void handleInterruptPin1() {
  if ( digitalRead(buttonPin1) == LOW )
  {
          buttonPin1Pressed=millis();
  }
  handleModeButton();
}

void handleInterruptPin2() {
  if ( digitalRead(buttonPin2) == LOW )
  {
          buttonPin2Pressed=millis();
  }
  handleModeButton();
}
