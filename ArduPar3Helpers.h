#pragma once

// enable debug messages?!
#define DEBUG 0

// the instances of classes derived from AbstractArduPar3 maintain a global list. You can change the maximum number of settings here.
#define PAR_SETTINGS_MAX_NUMBER 32

// this determines the maximum parameter command length
#define PAR_SETTINGS_BUFFER_SIZE 32

// the instances of classes derived from AbstractArduPar3 maintain a global list. You can change the maximum number of settings here.
#define PAR_SETTINGS_MAX_NUMBER 32

// this determines the maximum parameter command length
#define PAR_SETTINGS_BUFFER_SIZE 32

/////////


#define TRACE(x)       \
  do                   \
  {                    \
    if (DEBUG)         \
      Serial.print(x); \
  } while (0)
#define TRACELN(x)       \
  do                     \
  {                      \
    if (DEBUG)           \
      Serial.println(x); \
  } while (0)


// due to a big mess of external bugs with progmem strings in Arduino on diffferent platforms, we use an abstraction layer for them
#if defined(ESP32)
#define ARDUPAR_F(x) (x)
#define ARDUPAR_CONST_CHAR const char
#define ARDUPAR_CONST_CHAR_P const char
#define ARDUPAR_CONST_STRLEN(x) strlen(x)
#define ARDUPAR_CONST_STRCMP(a,b) strcmp(a,b)
#define ARDUPAR_CONST_STRNCMP(a,b,len) strncmp(a,b,len)

#endif

#if defined(ESP8266)
#define ARDUPAR_F(x) (x)
#define ARDUPAR_CONST_CHAR const char
#define ARDUPAR_CONST_CHAR_P const char
#define ARDUPAR_CONST_STRLEN(x) strlen(x)
#define ARDUPAR_CONST_STRCMP(a,b) strcmp(a,b)
#define ARDUPAR_CONST_STRNCMP(a,b,len) strncmp(a,b,len)
#endif

#if defined(__AVR__)
#define ARDUPAR_F(x) F(x)
#define ARDUPAR_CONST_CHAR_P const char PROGMEM
#define ARDUPAR_CONST_CHAR __FlashStringHelper
#define ARDUPAR_CONST_STRLEN(x) strlen_P(x)
#define ARDUPAR_CONST_STRCMP(a,b) strcmp_P(a,b)
#define ARDUPAR_CONST_STRNCMP(a,b,len) strncmp_P(a,b,len)

#endif
