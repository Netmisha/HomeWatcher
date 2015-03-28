#ifndef Watcher_h
#define Watcher_h
#include "config.h"

class Watcher {
  public:
    Watcher();

    void init();
    void read();
    void proceed();
    void show();
};

#endif//Watcher_h
