#include "Clock.h"
#include "config.h"
#include "Wire.h"
Clock::Clock(){
    mSecond = 0;
    mMinute = 0;
    mHour = 0;
    mDayOfWeek = 0;
    mDayOfMonth = 0;
    mMonth = 0;
    mYear = 0;
}

bool Clock::update(){
  Log::d("Clock::update");
	Wire.beginTransmission(DS1307_I2C_ADDRESS);
	Wire.write(decToBcd(0));
	Wire.endTransmission();
	Wire.requestFrom(DS1307_I2C_ADDRESS, 7);
	mSecond     = bcdToDec(Wire.read() & 0x7f);
	mMinute     = bcdToDec(Wire.read());
	mHour       = bcdToDec(Wire.read() & 0x3f);  // Need to change this if 12 hour am/pm
 	mDayOfWeek  = bcdToDec(Wire.read());
 	mDayOfMonth = bcdToDec(Wire.read());
 	mMonth      = bcdToDec(Wire.read());
 	mYear       = bcdToDec(Wire.read()); 
}

void Clock::print(){
  #ifdef LOG_DEBUG
	Serial.print("Time: ");
 	Serial.print(mHour, DEC);
 	Serial.print(":");
 	Serial.print(mMinute, DEC);
 	Serial.print(":");
 	Serial.print(mSecond, DEC);
 	Serial.print("  ");
 	Serial.print(mMonth, DEC);
 	Serial.print("/");
 	Serial.print(mDayOfMonth, DEC);
 	Serial.print("/");
 	Serial.print(mYear,DEC);
 	Serial.println();
  #endif
}

byte Clock::decToBcd(byte val)
{
 return ( (val/10*16) + (val%10) );
}
// Convert binary coded decimal to normal decimal numbers
byte Clock::bcdToDec(byte val)
{
 return ( (val/16*10) + (val%16) );
}

void Clock::setupClock(){
  Wire.beginTransmission(DS1307_I2C_ADDRESS);
  Wire.write(decToBcd(0));
  Wire.write(decToBcd(mSecond));
  Wire.write(decToBcd(mMinute));
  Wire.write(decToBcd(mHour));
  Wire.write(decToBcd(mDayOfWeek));
  Wire.write(decToBcd(mDayOfMonth));
  Wire.write(decToBcd(mMonth));
  Wire.write(decToBcd(mYear));
  Wire.endTransmission();
}