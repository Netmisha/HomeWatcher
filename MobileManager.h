#ifndef MobileManager_h
#define MobileManager_h
#include "Arduino.h"
#include <SoftwareSerial.h>

/*
http://smstools3.kekekasvi.com/topic.php?id=288

text: Alarm!!!
AT+CMGF=0
AT+CMGS=21
0011000C918390087096960000FF08417658DE0E8542
*/

class MobileManager{
	SoftwareSerial *m_pPhone;

	int m_portNumber;
        const int SEND_DELAY_TIME = 1500;
public:
	MobileManager(int rx, int tx);
	~MobileManager();
	bool isOK();
	bool isAT();
        void sendDelay();
	bool sendAlarm();
};
#endif
