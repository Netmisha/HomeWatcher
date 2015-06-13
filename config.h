#ifndef config_h
#define config_h
#include "Arduino.h"
#include "Log.h"


//#define LOG_DEBUG;

//Output Pins
//1.GND
//2.VCC
//3.RX
//4.TX
//5.DTR
//6.--
//7.TX Phone
//8.RX Phone
//9.GAS
//10.Move sensor
//11. Light
//12. --
//13. --
//14. Door Sensor out
//15. Door Sensor in
//16. 
//17. 
//18. 
//19. 
//20. 
//21. 
//22. 
//23. 
//24. 
//25. 

//#define LOG_DEBUG;

const int GAS_MAX_VAL = 500;
const int MOVE_MAX_VAL = 500;

//const unsigned long SECURITY_DELAY_TIME = 20 * 1000;//Test
const unsigned long SECURITY_DELAY_TIME = 60000;

const unsigned long BLINK_DELAY_TIME = 1000;
const unsigned long CHECK_DELAY_TIME = 100;

const int REGULAR_CHECK = 2;

const int PIN_AVAILABLE_0 = 0;
const int PIN_AVAILABLE_1 = 1;
const int PIN_MOBILE_TX_2 = 2;
const int PIN_MOBILE_RX_3 = 3;
const int PIN_DOOR_SENSOR_ACTIVATOR = 4;
const int PIN_BUZZER_5 = 5;
const int PIN_AVAILABLE_6 = 6;
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
const int PIN_CHIP_IN_DOOR_SENSOR_5 = 5;
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
