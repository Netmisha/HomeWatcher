#include"Log.h"
#include "config.h"
void Log::init(){
  Serial.begin(9600);
}
void Log::m(char* tag, char * msg){
  Serial.println(strcat(tag, msg));
}
void Log::e(char * msg){
  m("ERR: ", msg);
}
void Log::w(char * msg){
  m("WRG: ", msg);
}
void Log::d(char * msg){
  #ifdef LOG_DEBUG
    m("DBG: ", msg);
  #endif
}
