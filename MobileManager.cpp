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
  Serial.println("isAT Begin");
  m_pPhone->println("AT");
  delay(1500);
  return isOK();
}

void MobileManager::sendDelay() {
  delay(SEND_DELAY_TIME);
}
bool MobileManager::sendAlarm() {
  m_pPhone->println("AT+CMGF=0");
  delay(1500);
  m_pPhone->println("AT+CMGS=21");
  delay(1500);
  m_pPhone->print("0011000C918390087096960000FF08417658DE0E8542");
  m_pPhone->println((char)26);
  delay(1500);
  return isOK();
}
