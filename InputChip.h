#ifndef InputChip_h
#define inputChip_h
#include "config.h"

class InputChip {
    static const int PIN_COUNT = 8;
    bool pins[PIN_COUNT];


    int pinRCK;//Latch
    int pinSCK;//SHIFT CLOCK
    int pinSI;//Data




  public:
    InputChip(int RCK, int SCK, int SI);

    bool getValue(int pin);
    bool reset();
    bool update();

    void print();
};

#endif//OutputChip
