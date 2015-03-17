#ifndef OutputChip_h
#define OutputChip_h

class OutputChip{
  
  bool pins[8];
  
  
  int pinRCK;//Latch
  int pinSCK;//SHIFT CLOCK
  int pinSI;//Data
  
  
  
  public:
  OutputChip(int RCK, int SCK, int SI);
  
  bool setValue(int pin, int value);
  bool setValue(int pin, bool value);
  bool getValue(int pin);
  
  bool setHight(int pin);
  bool setLow(int pin);
  bool reset();
  
  bool flush();
};

#endif//OutputChip
