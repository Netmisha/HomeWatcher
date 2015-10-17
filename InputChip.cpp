#include "Arduino.h"
#include "InputChip.h"

InputChip::InputChip(int RCK, int SCK, int SI):
  pinRCK(RCK),
  pinSCK(SCK),
  pinSI(SI) {

  pinMode(pinRCK, OUTPUT);
  pinMode(pinSCK, OUTPUT);
  pinMode(pinSI, INPUT);

  reset();
}

bool InputChip::getValue(int pin) {
  return pins[pin];
}

bool InputChip::reset() {
  for (int i = 0; i < 8; i++) {
    pins[i] = false;
  }
  return true;
}
void InputChip::print() {
  Log::d("InputChip");
  for (int i = 0; i < 8; i++) {
    Serial.print(pins[i]);
    Serial.print(",");
  }
  Serial.println("");
}

bool InputChip::update() {
  Log::d("InputChip::update()");
  long bitVal;
  reset();
  digitalWrite(pinSCK, LOW);
  digitalWrite(pinRCK, LOW);
  delayMicroseconds(PULSE_WIDTH_READ_USEC);
  digitalWrite(pinRCK, HIGH);

  for (int i = 7; i >= 0; i--) {
    long val = digitalRead(pinSI);
    pins[i] = ((val == 0) ? LOW : HIGH);

    digitalWrite(pinSCK, LOW);
    delayMicroseconds(PULSE_WIDTH_READ_USEC);
    digitalWrite(pinSCK, HIGH);
  }

  digitalWrite(pinSCK, LOW);
  digitalWrite(pinRCK, LOW);
}
