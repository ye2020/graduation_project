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
void IR_on_send(void);
void IR_off_send(void);
void IR_temp_up_send(void);
void IR_temp_dowm_send(void);
void IR_power_send(void);

void IR_on_send_2(void);
void IR_off_send_2(void);
void IR_power_send_2(void);
void IR_temp_up_send_2(void);
void IR_temp_dowm_send_2(void);


extern void (*ac_func[3])(void);      // 函数指针数组

#endif