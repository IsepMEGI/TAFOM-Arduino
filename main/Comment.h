#if !defined(COMMENT_H)
#define COMMENT_H

#include <Arduino.h>

#if false
  #define sp(...) Serial.print(__VA_ARGS__);
  #define spl(...) Serial.println(__VA_ARGS__);
#else
  #define sp(...)
  #define spl(...)
#endif


#endif // Comment.h


