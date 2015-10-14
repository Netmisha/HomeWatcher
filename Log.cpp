#include"Log.h"
#include "config.h"
void Log::init() {
  Serial.begin(9600);
}
void Log::m(char* tag, char * msg) {
  Serial.print(micros());
  Serial.print(": ");
  Serial.print(tag);
  Serial.println(msg);
}

void Log::m(char* tag, char * msg, unsigned long val) {
  Serial.print(micros());
  Serial.print(": ");
  Serial.print(tag);
  Serial.print(msg);
  Serial.print(" val=");
  Serial.println(val);
}
void Log::e(char * msg) {
  m("ERR: \0", msg);
}
void Log::w(char * msg) {
  m("WRG: \0", msg);
}
void Log::d(char * msg) {
#ifdef LOG_DEBUG
  m("DBG: \0", msg);
#endif
}

void Log::d(char * msg, unsigned long val) {
#ifdef LOG_DEBUG
  m("DBG: \0", msg, val);
#endif
}

void Log::i(char * msg) {
  m("INF: \0", msg);
}
