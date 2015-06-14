#include "Arduino.h"
#include "OutputChip.h"

OutputChip::OutputChip(int RCK, int SCK, int SI):
  pinRCK(RCK),
  pinSCK(SCK),
  pinSI(SI) {

  pinMode(pinRCK, OUTPUT);
  pinMode(pinSCK, OUTPUT);
  pinMode(pinSI, OUTPUT);

  reset();
  mDataChanged = true;
}

bool OutputChip::setValue(int pin, bool value) {
  if(pins[pin] != value){
    pins[pin] = value;
    mDataChanged = true;
  }
  return true;
}

bool OutputChip::setValue(int pin, int value) {
  Log::d("OutputChip::setValue", value);
  return setValue(pin , value == 0 ? false : true);
}

bool OutputChip::getValue(int pin) {
  return pins[pin];
}

bool OutputChip::setHight(int pin) {
  return setValue(pin, HIGH);
}
bool OutputChip::setLow(int pin) {
  return setValue(pin, LOW);
}
bool OutputChip::reset() {
  for (int i = 0; i < PIN_COUNT; i++) {
    setValue(i, false);
  }
  return true;
}

bool OutputChip::flush() {
  Log::d("OutputChip::flush()");
  if(!mDataChanged){
    Log::d("No data was changed");
    return false;
  }
  digitalWrite(pinRCK, LOW);
  for (int i = PIN_COUNT-1; i >= 0; i--) {
    digitalWrite(pinSCK, LOW);
    digitalWrite(pinSI, pins[i] == true ? HIGH : LOW);
    digitalWrite(pinSCK, HIGH);
  }
  digitalWrite(pinRCK, HIGH);
  mDataChanged = false;
}

void OutputChip::print() {
  Log::d("OutputChip: ");
  for (int i = 0; i < PIN_COUNT; i++) {
    Serial.print(pins[i]);
    Serial.print(",");
  }
  Serial.println("");
}
