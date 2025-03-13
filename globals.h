#ifndef GLOBALS_H
#define GLOBALS_H

#include <RTC.h>

extern MedConfig globalConfig[10];
extern RTC_DS1307 rtc;
extern LCDStatus displayStatus;
extern ezBuzzer buzzer;

#endif
