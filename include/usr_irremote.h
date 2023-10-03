 /****************************** Y.Z.T.****************************************
  * @file       usr_irremote.c/h
  * @brief      遥控 , 红外发射与接收解析
  * @note
  * @history    2023.9.25
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
#ifndef _USR_IRREMOTE_H
#define _USR_IRREMOTE_H

#include <Arduino.h>

void IR_init(void);
void IR_receive(void);
void IR_send(void);



#endif