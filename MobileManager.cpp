#include "MobileManager.h"


MobileManager::MobileManager(int rx, int tx) {
  m_pPhone = new SoftwareSerial(rx, tx); // RX, TX
  m_pPhone->begin(9600);
}

MobileManager::~MobileManager() {
  delete m_pPhone;
}

bool MobileManager::isOK() {
  int len = m_pPhone->available();
  Log::d("available", len);
  char buff[128];
  if (len)
  {
    for (int i = 0; i < len; i++) {
      buff[i] = m_pPhone->read();
    }
    buff[len] = '\n';
    if (strcmp("OK", buff))
    {
      return true;
    }
  }
  return false;
}

bool MobileManager::isAT() {
  Log::d("isAT Begin");
  m_pPhone->println("AT");
  delay(1500);
  return isOK();
}

void MobileManager::sendDelay() {
  delay(SEND_DELAY_TIME);
}
bool MobileManager::sendAlarm() {
  Log::d("sendAlarm()");
  if (!isAT())
  {
    return false;
  }
  m_pPhone->println("AT+CMGF=0");
  delay(1500);
  m_pPhone->println("AT+CMGS=21");
  delay(1500);
  m_pPhone->print("0011000C918390087096960000FF08417658DE0E8542");
  m_pPhone->println((char)26);
  delay(1500);
  return isOK();
}

bool MobileManager::sendGas(){
  Log::d("sendGas()");
  if (!isAT())
  {
    return false;
  }
  m_pPhone->println("AT+CMGF=0");
  delay(1500);
  m_pPhone->println("AT+CMGS=20");
  delay(1500);
  m_pPhone->print("0011000C918390087096960000FF06C7F03C140A01");
  m_pPhone->println((char)26);
  delay(1500);
  return isOK();
}
