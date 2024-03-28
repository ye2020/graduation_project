#include "usr_SR505.h"

#if 0
const int SR_PIN = 13;

void sr_init(void)
{
    pinMode(SR_PIN, INPUT);
}


bool sr_tick(void)
{
    if(digitalRead(SR_PIN))
    {
        return true;
    }
    else
    {
        return false;
    }

    return false;
}

#endif