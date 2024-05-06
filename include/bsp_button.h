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
#ifndef _BSP_BUTTON_H
#define _BSP_BUTTON_H


#include "Arduino.h"

// 定义枚举变量 按键当前状态
typedef enum
{
    button_none = 0,        // 什么都没干
	  button_click = 1,       // 按键短按1次
    button_doubleclick ,    // 按键短按2次
    button_longPressStart , // 按键长按开始判定
    button_longPress,      // 按键长按中
    button_longPressStop,  // 按键长按结束判定

    button_click2,       // 按键短按1次
    button_doubleclick2 ,    // 按键短按2次
    button_longPressStart2 , // 按键长按开始判定
    button_longPress2,      // 按键长按中
    button_longPressStop2,  // 按键长按结束判定
} button_status_e;



void button_init(void);
void button_loop(void) ; 

button_status_e key5_status_return(void);
button_status_e key0_status_return(void);


/*************************** 按键5回调函数  *********************************/

void click1();
void doubleclick1() ;
void longPressStart1() ;
void longPress1() ;
void longPressStop1() ;

/*************************** 按键0回调函数  *********************************/
void click2() ;
void doubleclick2() ;
void longPressStart2();
void longPress2() ;
void longPressStop2() ;



#endif