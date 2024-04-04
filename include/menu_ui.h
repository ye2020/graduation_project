/**
  ****************************** Y.Z.T.****************************************
  * @file       menu_ui.c/h
  * @brief      提供菜单框架中UI的处理
  * @note
  * @history    2022.7.8
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
#ifndef __MENU_UI_H
#define __MENU_UI_H

#include "menu.h"
#include <Arduino.h>


void Menu_Main_Init(void);

void Enter_Page(menu_i32 index, button_status_e Key5Value, button_status_e Key0Value);

void main_page_ui_process(void);
void wifi_page_ui_process(void);
void select_page_ui_process(void);
void wifi_smart_conf_ui_process(void);
void wifi_discon_ui_process(void);
void wifi_info_ui_process(void);
void temp_hum_ui_process(void);
void wechat_ui_process(void);
void about_ui_process(void);
void ir_check_ui_process(bool status);
void remote_page_ui_process(void);
void led_color_ui_process(void);
void led_mode_ui_process(void);
void led_brightness_ui_process(void);





#endif