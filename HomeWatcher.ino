#include "config.h"
#include <Wire.h>
#include <SoftwareSerial.h>
#include "MobileManager.h"
#include "OutputChip.h"
#include "InputChip.h"
#include "Clock.h"

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
bool mSenDoor = false;

bool mRemBtnA = false;
bool mRemBtnB = false;
bool mRemBtnC = false;
bool mRemBtnD = false;

bool mLightOn = false;
bool mFilterOn = false;

long mReguilarIteration = REGULAR_CHECK;

int mSenGas = 0;
int mSenMove = 0;

MobileManager mobManager(PIN_MOBILE_RX_3, PIN_MOBILE_TX_2);
OutputChip pinMonitor(PIN_CHIP_OUT_LATCH, PIN_CHIP_OUT_CLOCK, PIN_CHIP_OUT_DATA);
InputChip pinConsole(PIN_CHIP_IN_LATCH, PIN_CHIP_IN_CLOCK, PIN_CHIP_IN_DATA);

Clock clk;
void SerenaTone(int nTimes){
  for(int n=0;n<nTimes;n++){
    for( int i=1; i<999; i++)
    { 
      tone(PIN_BUZZER_5,500+i*3,2000);
    }
    for( int i=999; i>1; i--)
    { 
      tone(PIN_BUZZER_5,500+i*3,2000);
    }
  }
  noTone(PIN_BUZZER_5);
}

void setup() {
  Wire.begin();
  Log::init();
  Log::d("Setup Begin");
  
  pinMode(PIN_DOOR_SENSOR_ACTIVATOR, OUTPUT);
  
  pinMonitor.setValue(PIN_CHIP_REMOTE_0_LIGHT, false);//Turn off
  pinMonitor.setValue(PIN_CHIP_REMOTE_1_FILTER, false);//Turn off
  
  pinMonitor.flush();
  
  Log::d("Setup End");
}

void readData() { 
  digitalWrite(PIN_DOOR_SENSOR_ACTIVATOR, HIGH); 
  pinConsole.update();

  mBtnReset = pinConsole.getValue(PIN_CHIP_IN_BTN_RESET_0);
  mBtnAlarm = pinConsole.getValue(PIN_CHIP_IN_BTN_ALARM_1);
  mBtnSecurity = pinConsole.getValue(PIN_CHIP_IN_BTN_SECURITY_2);
  
  mRemBtnA = pinConsole.getValue(PIN_CHIP_IN_BTN_A);
  mRemBtnB = pinConsole.getValue(PIN_CHIP_IN_BTN_B);
  mRemBtnC = pinConsole.getValue(PIN_CHIP_IN_BTN_C);
  mRemBtnD = pinConsole.getValue(PIN_CHIP_IN_BTN_D);
  
  if(mRemBtnA){
    mBtnAlarm = true;
  }
  
  if(mRemBtnC){
    mLightOn = !mLightOn;
  }
  
  if(mRemBtnB){
    mFilterOn = !mFilterOn;
  }
  
  Log::d("mRemBtnA: ", mRemBtnA);
  Log::d("mRemBtnB: ", mRemBtnB);
  Log::d("mRemBtnC: ", mRemBtnC);
  Log::d("mRemBtnD: ", mRemBtnD);
  digitalWrite(PIN_DOOR_SENSOR_ACTIVATOR, LOW);
  

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

unsigned long lastTime = 0;

void onSecond(){
  Log::d("onSecond");
  clk.update();
  clk.print();

  if (clk.mHour >= 8 && clk.mHour < 23)
  {
    Log::d("Day time");
    if (clk.mHour <= 9 || clk.mHour >= 19)
    {
      Log::d("Light on");
      pinMonitor.setValue(PIN_CHIP_REMOTE_0_LIGHT, true);//Turn on
    }else{
      Log::d("Light off");
      pinMonitor.setValue(PIN_CHIP_REMOTE_0_LIGHT, false);//Turn off
    }

    if (clk.mMinute >= 0 && clk.mMinute < 15)
    {
      Log::d("Filter on");
      pinMonitor.setValue(PIN_CHIP_REMOTE_1_FILTER, true);//Turn On  
    }else{
      Log::d("Filter off");
      pinMonitor.setValue(PIN_CHIP_REMOTE_1_FILTER, false);//Turn off
    }
  }else{
    Log::d("Night time");
    pinMonitor.setValue(PIN_CHIP_REMOTE_0_LIGHT, false);//Turn off
    pinMonitor.setValue(PIN_CHIP_REMOTE_1_FILTER, false);//Turn off
  }
  
  if(mLightOn){
    pinMonitor.setValue(PIN_CHIP_REMOTE_0_LIGHT, true);//Turn on
  }
  
  if(mFilterOn){
    pinMonitor.setValue(PIN_CHIP_REMOTE_1_FILTER, true);//Turn On
  }
  
  pinMonitor.flush();
}

void loop() {
  Log::d("***************BEGIN***************", mReguilarIteration);
  Log::d("mCurentState", mCurentState);
  unsigned long startTime = millis();
  if (abs(startTime - lastTime)>1000)
  {
    lastTime = startTime;
    onSecond();
  }
  #ifdef LOG_DEBUG
    delay(1000);
  #endif
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
  mSenGas =0;
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
      if(mSenDoor){
        Log::d("isDoorSensorDetected");
        //SerenaTone(1);
        tone(PIN_BUZZER_5, 200, 30);
      }
      break;
    case WARNING:
      Log::d("WARNING");
      break;
    case SECURITY:
      Log::d("SECURITY");
      //mSenMove = pinConsole.getValue(PIN_CHIP_IN_SENSOR_MOVE_4);//TODO: uncomment
      if (mSenMove || mSenDoor) {
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
      
      SerenaTone(1);
      break;
    default:
      Log::d("Unknown state");
      break;
  }

  if (mCurentState!=ALARM){
    mReguilarIteration++;
  }
}
