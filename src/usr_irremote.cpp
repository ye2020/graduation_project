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
IRrecv irrecv(kRecvPin);            // 创建一个接收实例

decode_results results;             // 接收区


void (*ac_func[3])(void) = {IR_power_send, IR_on_send, IR_off_send};           // 函数指针数组

    

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

// 发送开启指令
void IR_on_send(void)
{
    gree_ac.on();
    Serial.println(gree_ac.toString());         //显示发送的空调开机红外编码
    gree_ac.send();                             //发送红外命令
    // delay(2000);                             //测试阶段每两秒发一次
}

// 发送关闭指令
void IR_off_send(void)
{
    gree_ac.off();
    Serial.println(gree_ac.toString());         //显示发送的空调开机红外编码
    gree_ac.send();                             //发送红外命令
}

// 发送升温指令
void IR_temp_up_send(void)
{
    uint8_t temp;
    temp = gree_ac.getTemp();
    gree_ac.setTemp(temp + 1);
    Serial.println(gree_ac.toString());         //显示发送的空调开机红外编码
    gree_ac.send();                             //发送红外命令
    Serial.println("ac up");
}

// 发送降温指令
void IR_temp_dowm_send(void)
{
    uint8_t temp;
    temp = gree_ac.getTemp();
    gree_ac.setTemp(temp - 1);
    Serial.println(gree_ac.toString());         //显示发送的空调开机红外编码
    gree_ac.send();                             //发送红外命令
    Serial.println("ac dowm");
}


// 开或关指令
void IR_power_send(void)
{
    if(gree_ac.getPower())
    {
        IR_on_send();
        Serial.println("ac on");
    }
    else
    {
        IR_off_send();
        Serial.println("ac off");
    }
}