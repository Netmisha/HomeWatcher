#include <LiquidCrystal.h>

#include "config.h"
#include <SoftwareSerial.h>
#include "MobileManager.h"
#include "OutputChip.h"
#include "InputChip.h"

enum DEV_STATE {
  REGULAR = 0,
  SECURITY,
  WARNING,
  ALARM
};

int mCurentState = REGULAR;

bool mBtnReset = false;
bool mBtnSecurity = false;
bool mBtnAlarm = false;

long mReguilarIteration = REGULAR_CHECK;

int mSenGas = 0;
int mSenMove = 0;

MobileManager mobManager(PIN_MOBILE_RX, PIN_MOBILE_TX);
OutputChip pinMonitor(PIN_CHIP_OUT_LATCH, PIN_CHIP_OUT_CLOCK, PIN_CHIP_OUT_DATA);
InputChip pinConsole(PIN_CHIP_IN_LATCH, PIN_CHIP_IN_CLOCK, PIN_CHIP_IN_DATA);

void setup() {
  Log::init();
  Log::d("Setup Begin");
  Log::d("Setup End");
}

void readData() {
  pinConsole.update();
  pinConsole.print();

  mBtnReset = pinConsole.getValue(PIN_CHIP_IN_BTN_RESET_0);
  mBtnAlarm = pinConsole.getValue(PIN_CHIP_IN_BTN_ALARM_1);
  mBtnSecurity = pinConsole.getValue(PIN_CHIP_IN_BTN_SECURITY_2);

  Log::d("mBtnReset", mBtnReset);
  Log::d("mBtnSecurity", mBtnSecurity);
  Log::d("mBtnAlarm", mBtnAlarm);
}

void ResetLeds() {
  Log::d("ResetLeds Begin");
  pinMonitor.setValue(PIN_CHIP_OUT_LED_ALARM_7, false);
  pinMonitor.setValue(PIN_CHIP_OUT_LED_GAS_6, false);
  pinMonitor.flush();
  Log::d("ResetLeds End");
}

bool ResetDelay(unsigned long mSec) {
  Log::d("ResetDelay Begin", mSec);
  unsigned long endTime = millis()+mSec;
  while(millis() < endTime){
    Log::d("Time remain: ", endTime - millis());
    pinConsole.update();
    if (pinConsole.getValue(PIN_CHIP_IN_BTN_RESET_0) || pinConsole.getValue(PIN_CHIP_IN_BTN_ALARM_1)) {
      Log::d("Reset by user");
      return true;
    }
    delay(CHECK_DELAY_TIME);
  }
  Log::d("ResetDelay End");
  return false;
}

bool BlinkAlarm(unsigned int nTimes) {
  for (int i = 0; i < nTimes; i++) {
    Log::d("BlinkLed", i);
    pinMonitor.setValue(PIN_CHIP_OUT_LED_ALARM_7, true);
    pinMonitor.flush();
    if (ResetDelay(BLINK_DELAY_TIME)) {
      pinMonitor.setValue(PIN_CHIP_OUT_LED_ALARM_7, false);
      pinMonitor.flush();
      return false;
    }
    pinMonitor.setValue(PIN_CHIP_OUT_LED_ALARM_7, false);
    pinMonitor.flush();
    if (ResetDelay(BLINK_DELAY_TIME)) {
      pinMonitor.setValue(PIN_CHIP_OUT_LED_ALARM_7, false);
      pinMonitor.flush();
      return false;
    }
  }
  return true;
}

void loop() {
  unsigned long startTime = micros();
  #ifdef LOG_DEBUG
    delay(1000);
  #endif

  Log::d("***************BEGIN***************");
  Log::d("mCurentState", mCurentState);
  Log::d("mReguilarIteration", mReguilarIteration);
  readData();

  if (mBtnReset) {
    mCurentState = REGULAR;
  } else if (mBtnAlarm) {
    mCurentState = ALARM;
  } else if (mBtnSecurity && mCurentState != ALARM) {
    if (BlinkAlarm(5) != false) {
      Log::d("SECURITY delay: ", SECURITY_DELAY_TIME);
      if(ResetDelay(SECURITY_DELAY_TIME)==false){// if not reseted by user
        mCurentState = SECURITY;
      }else{
        if (pinConsole.getValue(PIN_CHIP_IN_BTN_ALARM_1))
        {
          Log::d("Switch to ALARM");
          mCurentState = ALARM;
        } 
      }
      
    } else {
      Log::d("SECURITY reset by user");
      if (pinConsole.getValue(PIN_CHIP_IN_BTN_ALARM_1))
        {
          Log::d("Switch to ALARM");
          mCurentState = ALARM;
        }
    }
  }

  mSenGas = analogRead(PIN_ANALOG_0_SEN_GAS);
  Log::d("Gas Sensor", mSenGas);
  if (mSenGas > GAS_MAX_VAL) {
    Log::d("GAS_MAX_VAL", GAS_MAX_VAL);
    mCurentState = ALARM;
    pinMonitor.setValue(PIN_CHIP_OUT_LED_GAS_6, true);
    if (mReguilarIteration>=REGULAR_CHECK)
    {
      mReguilarIteration = 0;
      mobManager.sendGas();
    }

  }

  switch (mCurentState) {
    case REGULAR:
      Log::d("REGULAR");
      ResetLeds();
      break;
    case WARNING:
      Log::d("WARNING");
      break;
    case SECURITY:
      Log::d("SECURITY");
      mSenMove = pinConsole.getValue(PIN_CHIP_IN_SENSOR_MOVE_4);
      if (mSenMove) {
        Log::d("Moving Detected");
        if (BlinkAlarm(10) == true) {
          mCurentState = ALARM;
        }
      }
      break;
    case ALARM:
      Log::d("ALARM");
      pinMonitor.setValue(PIN_CHIP_OUT_LED_ALARM_7, true);
      pinMonitor.flush();

      if (mReguilarIteration>=REGULAR_CHECK)
      {
        mReguilarIteration = 0;
        mobManager.sendAlarm();
      }
      break;
    default:
      Log::d("Unknown state");
      break;
  }

  if (mCurentState!=ALARM){
    mReguilarIteration++;
  }
  pinMonitor.print();
  Log::d("****************END****************", micros() - startTime);
}
