/**
  ****************************** Y.Z.T.****************************************
  * @file       usr_eeprom.c/h
  * @brief      用于存放写入和读取flash的函数
  * @note       none
  * 
  * @author     Y.Z.T
  * @history    2023.9.18
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */

#ifndef _USR_EEPROM_H
#define _USR_EEPROM_H

#include <Arduino.h>
#include "usr_ws2812.h"




/** EEPROM结构体 , 写入内存的值  **/
struct EEPROMStruct
{
    uint8_t auto_state;         // 自动刷写eeprom状态 0-需要 1-不需要
    char wifi_ssid[32];         // 上次连接的wifi的ssid
    char wifi_password[64];     // 上次连接的wifi的密码

    uint8_t eeprom_Brightness;          // 初始亮度
    WS_LED_mode_e eeprom_LED_mode;      // LED模式
    uint32_t eeprom_LED_color;          // LED颜色


};

extern EEPROMStruct eepUserSet;

#define eeprom_address0 0       //起始地址




void auto_eeprom(void);                 // 自动读取EEPROM
void wifi_eeprom(const char* SSID,const char* Password);
void eeprom_read(void);
void LED_eeprom(uint8_t Brightness, WS_LED_mode_e LED_mode, uint32_t LED_color);

#endif
