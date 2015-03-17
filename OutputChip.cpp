#include "Arduino.h"
#include "OutputChip.h"

OutputChip::OutputChip(int RCK, int SCK, int SI):
  pinRCK(RCK),
  pinSCK(SCK),
  pinSI(SI){
    
  pinMode(pinRCK, OUTPUT);  
  pinMode(pinSCK, OUTPUT);
  pinMode(pinSI, OUTPUT);
  
  reset();
}
  
bool OutputChip::setValue(int pin, bool value){
  pins[pin]=value;
  return true;
}

bool OutputChip::setValue(int pin, int value){
  return setValue(pin ,value==0?false:true);
}

bool OutputChip::getValue(int pin){
  return pins[pin];
}
  
bool OutputChip::setHight(int pin){
  return setValue(pin, HIGH);
}
bool OutputChip::setLow(int pin){
  return setValue(pin, LOW);
}
bool OutputChip::reset(){
  for(int i=0;i<8;i++){
    pins[i]=false;
  }
  return true;
}

bool OutputChip::flush(){
  Serial.println("OutputChip::flush()");
  digitalWrite(pinRCK, LOW);
  for(int i=7;i>=0;i--){
    digitalWrite(pinSCK, LOW);
      digitalWrite(pinSI, pins[i]==true?HIGH:LOW);
    digitalWrite(pinSCK, HIGH);
  }  
  digitalWrite(pinRCK, HIGH);
}
