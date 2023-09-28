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

void main_page_ui_process(menu_u8 index);
void weather_page_ui_process(void);
void clock_page_ui_process(void);
void select_page_ui_process(void);
void setting_page_ui_process(void);
void language_page_ui_process(void);
void word_page_ui_process(void);
void configuration_page_ui_process(void);
void read_page_ui_process(void);
void book_page_ui_process(void);


#endif