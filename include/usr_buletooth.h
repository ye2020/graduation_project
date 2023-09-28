#ifndef _USR_BULETOOTH_H
#define _USR_BULETOOTH_H

#include <Arduino.h>
#include "bsp_button.h"



void buletooth_loop(void);
button_status_e keybt0_status_return(void);
button_status_e keybt1_status_return(void);



#endif
