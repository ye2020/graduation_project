#ifndef _USR_CLOCK_TIME_H
#define _USR_CLOCK_TIME_H

#include <Arduino.h>

typedef struct 
{
   String time_hours;
   String time_minutes;
}usr_time_t;


void clock_init(void);
void clock_updata(void);

String return_time_hours(void);
String return_time_minutes(void);



#endif