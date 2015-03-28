#ifndef config_h
#define config_h
#include "Arduino.h"
#include "Log.h"


#define LOG_DEBUG;

const int GAS_MAX_VAL = 500;
const int MOVE_MAX_VAL = 500;

const unsigned long SECURITY_DELAY_TIME = 20 * 1000;
//const unsigned long SECURITY_DELAY_TIME = 3 * 60 * 1000;

const unsigned long BLINK_DELAY_TIME = 1000;
const unsigned long CHECK_DELAY_TIME = 100;


const int PIN_AVAILABLE_1 = 1;
const int PIN_AVAILABLE_2 = 2;
const int PIN_AVAILABLE_3 = 3;
const int PIN_AVAILABLE_4 = 4;
const int PIN_MOBILE_RX = 5;
const int PIN_MOBILE_TX = 6;
const int PIN_CHIP_IN_LATCH = 7;
const int PIN_CHIP_IN_CLOCK = 8;
const int PIN_CHIP_IN_DATA = 9;
const int PIN_AVAILABLE_10 = 10;
const int PIN_CHIP_OUT_DATA = 11;
const int PIN_CHIP_OUT_CLOCK = 12;
const int PIN_CHIP_OUT_LATCH = 13;


const int PIN_CHIP_IN_BTN_RESET_0 = 0;
const int PIN_CHIP_IN_BTN_ALARM_1 = 1;
const int PIN_CHIP_IN_BTN_SECURITY_2 = 2;
const int PIN_CHIP_IN_RMT_BLIDES_3 = 3;
const int PIN_CHIP_IN_SENSOR_MOVE_4 = 4;
const int PIN_CHIP_IN_AVAILABLE_5 = 5;
const int PIN_CHIP_IN_AVAILABLE_6 = 6;
const int PIN_CHIP_IN_AVAILABLE_7 = 7;


const int PIN_CHIP_OUT_AVAILABLE_0 = 0;
const int PIN_CHIP_OUT_AVAILABLE_1 = 1;
const int PIN_CHIP_OUT_AVAILABLE_2 = 2;
const int PIN_CHIP_OUT_AVAILABLE_3 = 3;
const int PIN_CHIP_OUT_AVAILABLE_4 = 4;
const int PIN_CHIP_OUT_AVAILABLE_5 = 5;
const int PIN_CHIP_OUT_LED_GAS_6 = 6;
const int PIN_CHIP_OUT_LED_ALARM_7 = 7;

const int PIN_ANALOG_0_SEN_GAS = 0;
const int PIN_ANALOG_AVAILABLE_1 = 1;
const int PIN_ANALOG_AVAILABLE_2 = 2;
const int PIN_ANALOG_AVAILABLE_3 = 3;
const int PIN_ANALOG_AVAILABLE_4 = 4;
const int PIN_ANALOG_AVAILABLE_5 = 5;
const int PIN_ANALOG_AVAILABLE_6 = 6;


#endif
