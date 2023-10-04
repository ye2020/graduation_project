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

#include "usr_eeprom.h"
#include <EEPROM.h>


EEPROMStruct eepUserSet;                // 用户写入 EEPROM 的结构体


/**
 * @brief       自动计算与写入EEPROM的函数
 * @param[in]   none
 * @retval      
 * @attention   首次开机自动刷写一部分EEPROM, 以及读取eeprom中的数据
 */
void auto_eeprom(void){
  
  /* 自动计算需要用多少eeprom数量 */
  EEPROM.begin(sizeof(EEPROMStruct));


  /* 获取eeprom数据 */
  EEPROM.get(eeprom_address0,eepUserSet);



  /* 只需要刷写一次的部分 */
  if (eepUserSet.auto_state != 1) eepUserSet.auto_state = 0;
  if (eepUserSet.auto_state == 0){
    Serial.println("正在写入EEPROM");
    Serial.println("请不要进行其他操作");
    
    strcpy(eepUserSet.wifi_ssid, String("00_mi").c_str());                             // 默认 wifi 的ssid
    strcpy(eepUserSet.wifi_password, String("yezhaotin").c_str());                     // 默认 wifi 的pwd
    eepUserSet.auto_state = 1;                                    // 表示后面不需要在刷写


    EEPROM.put(eeprom_address0, eepUserSet);
    EEPROM.commit();                                              // 首次保存覆盖掉旧的数值
    Serial.println("EEPROM put");
      
    EEPROM.get(eeprom_address0,eepUserSet);                       // 重新 获取eeprom数据 
    
  }

  /* 每次开机都自动刷写的部分 , 比如说每次开机只读取flash 中保存的部分 */
  if (eepUserSet.auto_state == 1){
     Serial.println("EEPROM get");
  }

}


/**
 * @brief       将成功连接的wifi的参数写入 EEPROM
 * @param[in]   none
 * @retval      
 * @attention   将wifi 的ssid和pwd写入flash
 */
void wifi_eeprom(const char* SSID,const char* Password) {
    strcpy(eepUserSet.wifi_ssid, SSID);
    strcpy(eepUserSet.wifi_password, Password);
    EEPROM.put(eeprom_address0, eepUserSet);
    EEPROM.commit();                                              // 覆盖掉旧的数值

}


// 读取EEPROM数据
void eeprom_read(void)
{
  EEPROM.get(eeprom_address0,eepUserSet);
}