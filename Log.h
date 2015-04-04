#ifndef Log_h
#define Log_h

class Log {

  public:
    static void init();
    static void m(char* tag, char * msg);
    static void m(char* tag, char * msg, unsigned long val);
    static void e(char * msg);
    static void w(char * msg);
    static void d(char * msg);
    static void d(char * msg, unsigned long val);
};

#endif//Log_h
