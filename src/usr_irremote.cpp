/****************************** Y.Z.T.****************************************
  * @file       usr_irremote.c/h
  * @brief      遥控 , 红外发射与接收解析
  * @note
  * @history    2023.9.25
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
#include "usr_irremote.h"
#include <IRremoteESP8266.h>        // ESP8266 红外控制库
#include <IRsend.h>                 // 红外发射库
#include <IRrecv.h>                 // 红外接收库
#include <ir_Gree.h>                // 格力空调库


const uint16_t kRecvPin = 5;        // 接收io
const uint16_t ksendPin = 14;       // 发送io

IRGreeAC gree_ac(ksendPin);         // 创建一个格力空调的实例 

IRrecv irrecv(kRecvPin);

decode_results results;             // 接收区

// 红外接收初始化
void IR_init(void)
{
    gree_ac.begin();                // 开启空调红外 
    irrecv.enableIRIn();             // 启动红外接收
}

void IR_receive(void)
{
    if(irrecv.decode(&results)) 
    {
        Serial.println(results.value, HEX);
        Serial.println("");
        irrecv.resume();            // 接收下一个值
    }
}

void IR_send(void)
{
    gree_ac.on();
    // Serial.println(gree_ac.toString());         //显示发送的空调开机红外编码
    gree_ac.send();                         //发送红外命令
    delay(2000);                             //测试阶段每两秒发一次
}