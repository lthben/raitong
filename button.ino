void setup_button() {
  pinMode(buttonPin, INPUT_PULLUP);
  digitalWrite(ledPin, LOW);
}

void button_operation() {

  //   Serial.print("buttonState: ");
  //   Serial.println(buttonState);

  if ((millis() - lastDebounceTime) > debounceDelay) { //check only periodically

    buttonReading = digitalRead(buttonPin); //INPUT_PULLUP mode -> LOW means pressed, HIGH means NOT pressed

    if (buttonReading != lastButtonState) {

      if (buttonReading == LOW) {

        lastDebounceTime = millis(); //exact moment when pressed

//        Serial.print(F("do something once "));
//        Serial.println((millis());

        digitalWrite(ledPin, HIGH);

      } else if (buttonReading == HIGH) { //released

        digitalWrite(ledPin, LOW);
      }

      if (buttonReading != buttonState) {
        buttonState = buttonReading;
      }
      lastButtonState = buttonReading;
    }
  }
}


