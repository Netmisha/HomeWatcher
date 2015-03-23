#ifndef Log_h
#define Log_h

class Log{

  public:
  static void init();
  static void m(char* tag, char * msg);
  static void e(char * msg);
  static void w(char * msg);
  static void d(char * msg);
};

#endif//Log_h
