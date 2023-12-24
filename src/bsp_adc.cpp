/**
 * *********************************** Y.Z.T. *************************************
 * 
 * @file       bsp_adc.cpp
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
#include "bsp_adc.h"


#define ARRAY_DIM(a) (sizeof(a) / sizeof((a)[0]))

const int analogInPin = A0;      // 模拟输入引脚

#define checkBatTime 3 * 1000               // 读取电池电量速率1s (1s<=upDataTime<=60s）
unsigned long bat_vcc_preTick = 0;      // 上次读取电压时的心跳值
 
 
const static int Battery_Level_Percent_Table[11] = {3000, 3650, 3700, 3740, 3760, 3795, 3840, 3910, 3980, 4070, 4150};     // 电池电量表
int sensorvalue = 0;


/**
 * @brief 初始化adc
 * 
 * 
 */
void bsp_adc_init(void)
{
    pinMode(analogInPin, INPUT);    //设置引脚为输入模式
}


/**
 * @brief 读取adc数据
 * 
 * 
 * @return float 实时电压值  单位v
 */
float get_bat_vcc(void)
{
    float vcc_cache = 0.0;

    // 均值滤波
    for (uint8_t i = 0; i < 30; i++)
    {
        //delay(1);
        vcc_cache += analogRead(analogInPin) * 0.0009765625 * 4.70;          // (1/1024)* 采样分压值
        // vcc_cache += analogRead(analogInPin);
    }

    return(vcc_cache / 30);
}


/**
 * @brief 获取电池电量百分比    
 * 
 * 
 * @return 返回电池电量百分比
 */
uint8_t bat_vcc_percentage(void)
{
    static uint8_t bat_percen = 0;
    int voltage_value;                // 电压值,单位mv
    
    /* 每3秒获取一次电压值, 并返回电压百分比 */
    if(millis() - bat_vcc_preTick >= checkBatTime)
    {
        bat_vcc_preTick = millis();                           // 更新心跳值
        voltage_value = (int)(get_bat_vcc() * 1000);          // 获取当前电压值

        Serial.println("vcc: ");	
        Serial.println(voltage_value);	

        /* 电压小于最低电压 */
        if(voltage_value < Battery_Level_Percent_Table[0])
        {
            bat_percen = 0;
            return bat_percen;
        } 
            

        for(unsigned int i = 0; i < ARRAY_DIM(Battery_Level_Percent_Table); i++)
        {
            if(voltage_value < Battery_Level_Percent_Table[i])
            {
                // 百分比 计算可看成每10%的电量为一个固定斜率 即 10/(a[i]-a[i-1]) 以该斜率乘上区间内的电压值 (a[i]-voltage)
                bat_percen = i*10 - ((10UL * (int)(Battery_Level_Percent_Table[i] - voltage_value)) / 
                                             (int)(Battery_Level_Percent_Table[i] - Battery_Level_Percent_Table[i-1]));
            }
        }

       bat_percen = 100;
    }

    return bat_percen;
}