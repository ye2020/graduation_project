#include "usr_buletooth.h"
#include <SoftwareSerial.h>

SoftwareSerial BT(15);
const int BT_PIN = 15;

static String comdata = "";


extern button_status_e button5_current_state;
extern button_status_e button0_current_state;

void buletooth_init(void)
{
    BT.begin(9600);
    pinMode(BT_PIN, OUTPUT);
    digitalWrite(BT_PIN,0);
}

void buletooth_loop(void)
{
    // while(BT.available() > 0)               // 串口接收的数据大于0
    // {
    //     comdata += char(BT.read());
    //     Serial.println("Serial read");
    //     Serial.println(comdata);
    // }
     if(BT.available())
     {
        comdata = char(BT.read());
        Serial.println("Serial read");
        Serial.println(comdata);        
     }

    if(comdata == "j") {                                // 向下

        comdata = "";
        button5_current_state = button_click;
        button0_current_state = button_none;

        return;
    } else if (comdata == "l") {                        // 向上
        comdata = "";
        button5_current_state = button_none;
        button0_current_state = button_click2;

        return;
    } else if (comdata == "k") {                        // 确定
        comdata = "";
        button5_current_state = button_longPressStart;
        button0_current_state = button_none;

        return;
    } else if (comdata == "u") {                        // 返回
        comdata = "";
        button5_current_state = button_none;
        button0_current_state = button_longPressStart2;
    }
    else if (comdata == "o") {                        // home键
        comdata = "";
        button5_current_state = button_none;
        button0_current_state = button_doubleclick2;
    }
    else {
        comdata = "";
    //     button5_current_state = button_none;
    //     button0_current_state = button_none;
        return;        
    }    
}



/**
 * @brief       蓝牙按键0状态回调函数
 * @param[in]   none
 * @retval      
 * @attention   用于返回蓝牙按键0的状态值
 */
button_status_e keybt0_status_return(void)
{
    return button5_current_state;
}

/**
 * @brief       蓝牙按键1状态回调函数
 * @param[in]   none
 * @retval      
 * @attention   用于返回蓝牙按键1的状态值
 */
button_status_e keybt1_status_return(void)
{
    return button0_current_state;
}