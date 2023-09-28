#include "usr_buletooth.h"

static String comdata = "";


extern button_status_e button5_current_state;
extern button_status_e button0_current_state;

void buletooth_loop(void)
{
    while(Serial.available() > 0)               // 串口接收的数据大于0
    {
        comdata += char(Serial.read());
        Serial.println("Serial read");
        Serial.println(comdata);
    }

    if(comdata == "1") {
        comdata = "";
        button5_current_state = button_click;
        button0_current_state = button_none;
    } else if (comdata == "2") {
        comdata = "";
        button5_current_state = button_none;
        button0_current_state = button_click;
    } else if (comdata == "3") {
        comdata = "";
        button5_current_state = button_doubleclick;
        button0_current_state = button_none;
    } else {
        comdata = "";
        button5_current_state = button_none;
        button0_current_state = button_none;        
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