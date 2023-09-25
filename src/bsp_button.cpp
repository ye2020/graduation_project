/**
  ****************************** Y.Z.T.****************************************
  * @file       bsp_button.c/h
  * @brief      用于存放按键多功能检测的相关函数和结构体
  * @note       包括按键的短按，长按和双击等回调函数   
  * 
  * @author     Y.Z.T
  * @history    2023.9.25
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */

#include "OneButton.h"
#include "bsp_button.h"

/*********************** 变量定义 *************************/
OneButton key5(5, true);           // 定义按钮5（gpio5）  , 按键按下为低电平
OneButton key0(0,true);            // 定义按键0（gpio0）

static button_status_e button5_current_state = button_none;      // 按键5当前按键状态
static button_status_e button0_current_state = button_none;      // 按键0当前按键状态

/**********************  函数声明 ************************/


/**
 * @brief       按键初始化函数
 * @param[in]   none
 * @retval      none
 * @attention  在setup函数调用
 */
 void button_init(void)
 {
    // 按键5函数映射.
    key5.attachClick(click1);
    key5.attachDoubleClick(doubleclick1);
    key5.attachLongPressStart(longPressStart1);
    key5.attachLongPressStop(longPressStop1);
    key5.attachDuringLongPress(longPress1);

    // 按键0函数映射
    key0.attachClick(click2);
    key0.attachDoubleClick(doubleclick2);
    key0.attachLongPressStart(longPressStart2);
    key0.attachLongPressStop(longPressStop2);
    key0.attachDuringLongPress(longPress2);

 }


/**
 * @brief       按键循环函数，检测引脚输入
 * @param[in]   none
 * @retval      在loop函数调用
 * @attention
 */
  void button_loop(void)  
  {
    button5_current_state = button_none;  // 默认什么都没干，直到发生中断事件
    button0_current_state = button_none;  // 默认什么都没干，直到发生中断事件
    key5.tick();
    key0.tick();

  }


/**
 * @brief       按键5状态回调函数
 * @param[in]   none
 * @retval      
 * @attention   用于返回按键5的状态值
 */
button_status_e key5_status_return(void)
{
    return button5_current_state;
}

/**
 * @brief       按键0状态回调函数
 * @param[in]   none
 * @retval      
 * @attention   用于返回按键0的状态值
 */
button_status_e key0_status_return(void)
{
    return button0_current_state;
}

/*************************** 按键5回调函数  *********************************/

// 当key5被按下1次时，这个函数将被调用。
void click1()
{
  Serial.println("Button 1 click.");
  button5_current_state = button_click;    // 更新状态
} 


// 当key5短时间被按下2次时，这个函数将被调用。
void doubleclick1() 
{
  Serial.println("Button 1 doubleclick.");
  button5_current_state = button_doubleclick;    // 更新状态
} 


// 当长时间按下key5时，这个函数将被调用一次。
void longPressStart1() 
{
  Serial.println("Button 1 longPress start");
  button5_current_state = button_longPressStart;    // 更新状态
}


// 当长时间按下key5时，会一直调用这个函数。
void longPress1() 
{
  Serial.println("Button 1 longPress...");
  button5_current_state = button_longPress;    // 更新状态
}


// 当长时间按下key5释放后,这个函数将被调用一次
void longPressStop1() 
{
  Serial.println("Button 1 longPress stop");
  button5_current_state = button_longPressStop;    // 更新状态
}


/*************************** 按键0回调函数  *********************************/

void click2() 
{
  Serial.println("Button 2 click.");
  button0_current_state = button_click2;    // 更新状态
} 


void doubleclick2() 
{
  Serial.println("Button 2 doubleclick.");
  button0_current_state = button_doubleclick2;    // 更新状态
} 


void longPressStart2()
{
  Serial.println("Button 2 longPress start");
  button0_current_state = button_longPressStart2;    // 更新状态
}


void longPress2() 
{
  Serial.println("Button 2 longPress...");
  button0_current_state = button_longPress2;    // 更新状态
} 

void longPressStop2() 
{
  Serial.println("Button 2 longPress stop");
  button0_current_state = button_longPressStop2;    // 更新状态
}

