#include "Arduino.h"
#include "OutputChip.h"

#define PULSE_WIDTH_USEC   5

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
    Log::d("OutputChip::setValue mDataChanged");
    print();
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
  if(!mDataChanged){
    Log::d("OutputChip::flush() no data changed");
    return false;
  }
  Log::d("OutputChip::flush() flushing");
  digitalWrite(pinRCK, HIGH);
  delay(PULSE_WIDTH_USEC);
  digitalWrite(pinRCK, LOW);
  delay(PULSE_WIDTH_USEC);
  for (int i = PIN_COUNT-1; i >= 0; i--) {
    digitalWrite(pinSCK, LOW);
    delay(PULSE_WIDTH_USEC);
    digitalWrite(pinSI, pins[i] == true ? HIGH : LOW);
    delay(PULSE_WIDTH_USEC);
    digitalWrite(pinSCK, HIGH);
    delay(PULSE_WIDTH_USEC);
  }
  digitalWrite(pinRCK, HIGH);
  delay(PULSE_WIDTH_USEC);
  digitalWrite(pinRCK, LOW);
  digitalWrite(pinSCK, LOW);
  digitalWrite(pinSI, LOW);
  mDataChanged = false;
  print();
}

void OutputChip::print() {
  Log::d("OutputChip: ");
  for (int i = 0; i < PIN_COUNT; i++) {
    Serial.print(pins[i]);
    Serial.print(",");
  }
  Serial.println("");
}
