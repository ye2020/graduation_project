/**
 * *********************************** Y.Z.T. *************************************
 * 
 * @file       bsp_adc.h
 * @brief 
 * 
 * @author     Y.Z.T      (yezhaotin@outlook.com)
 * @date       2023-12-22
 * ============================================================================== 
 *  
 * ==============================================================================
 * @version    1.0
 * *********************************** Y.Z.T. *************************************
 */
#ifndef _BSP_ADC_H
#define _BSP_ADC_H

#include "Arduino.h"

void bsp_adc_init(void);
float get_bat_vcc(void);
uint8_t bat_vcc_percentage(void);
bool return_recharge_state(void);



#endif