#ifndef Clock_h
#define Clock_h
#include "config.h"

#define DS1307_I2C_ADDRESS 0x68  // the I2C address of Tiny RTC

class Clock {
    byte decToBcd(byte val);
    byte bcdToDec(byte val);
    void setupClock();
  public:
    byte mSecond;
    byte mMinute;
    byte mHour;
    byte mDayOfWeek;
    byte mDayOfMonth;
    byte mMonth;
    byte mYear;
    Clock();
    bool update();
    void print();
};

#endif//Clock_h
