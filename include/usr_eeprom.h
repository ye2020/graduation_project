#ifndef _USR_EEPROM_H
#define _USR_EEPROM_H

#include <Arduino.h>



/** EEPROM结构体 , 写入内存的值  **/
struct EEPROMStruct
{
    uint8_t auto_state;         // 自动刷写eeprom状态 0-需要 1-不需要
    char wifi_ssid[32];         // 上次连接的wifi的ssid
    char wifi_password[64];     // 上次连接的wifi的密码
};

extern EEPROMStruct eepUserSet;

#define eeprom_address0 0       //起始地址




void auto_eeprom(void);                 // 自动读取EEPROM
void wifi_eeprom(const char* SSID,const char* Password);

#endif
