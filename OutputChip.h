#ifndef OutputChip_h
#define OutputChip_h
#include "config.h"

class OutputChip {
    static const int PIN_COUNT = 16;
    bool pins[PIN_COUNT];


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
    void print();
};

#endif//OutputChip
