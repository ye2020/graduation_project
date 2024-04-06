/**
  ****************************** Y.Z.T.****************************************
  * @file       menu.c/h
  * @brief      提供键值适配等UI菜单框架数据
  * @note          
  * @history    2023.9.20
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */

#ifndef __MENU_H
#define __MENU_H

#include "bsp_button.h"

extern uint8_t ui_loging_flag;
// 对应数据类型定义
typedef unsigned int   menu_u32;
typedef unsigned short menu_u16;
typedef unsigned char  menu_u8;

typedef int menu_i32 ;
typedef short menu_s16 ;
typedef char menu_s8 ;


// 键值定义枚举
typedef enum 
{
    KEY_none  = 0,
	  KEY_enter,          // 确定
    KEY_esc,            // 返回
    KEY_up,             // 向上
    KEY_dowm,           // 向下
    KEY_home,           // home键
    KEY_setting,        // 设置键

}key_value_e;

// 各界面索引，子菜单
typedef struct Menu_Key_Index
{
	menu_u8 main_current_index ;
	menu_u8 wifi_config_current_index ; 
  menu_u8 select_current_index;
  menu_u8 remote_current_index;
  menu_u8 color_current_index;
  menu_u8 mode_current_index;
  menu_u8 buletooth_current_index;

	menu_u8 Current_Page ;      // 当前页面
}Key_Index;


extern Key_Index sub_index ;

typedef void (*menu_op_func)(button_status_e , button_status_e);

typedef struct OP_STRUCT
{
	int op_menu ; 				//操作菜单
	menu_op_func opfun ;	//操作方法
}OP_MENU_PAGE;

/*当前菜单*/
typedef enum 
{
	MAIN_PAGE = 0,          // 主页面						
  SELECT_PAGE,            // 菜单页面   (1 ~ 10)索引为菜单页面及其子页面
  WiFi_PAGE,              // 网络配置页面  (select 下子表单）
  BULEBOOTH_PAGE,          // 蓝牙页面    (select 下子表单)
  WECHAT_PAGE,            // 微信小程序页面(select 下子表单)
  REMOTE_PAGE,            // 遥控页面      (select 下子表单)
  ABOUT_PAGE,             // 关于设备      (select 下子表单)
  WIFI_INFO_PAGE = 11,    // 当前网络信息    
  WIFI_DISCONNECT_PAGE,   // 断开网络
  WIFI_SMART_CON_PAGE,    // 智能配网(扫码)
  REMOTE_PWOER_PAGE= 16,  // LED开关
  REMOTE_COLOR_PAGE ,     // LED颜色设置页面 (remote 下子表单)
  REMOTE_MODE_PAGE,       // LED模式设置页面 (remote 下子表单)
  REMOTE_BRIGHTNESS_PAGE, // LED亮度设置页面 (remote 下子表单)
  REMOTE_COLOR_R_PAGE= 21,// LED 颜色R设置   (color 下子表单)
  REMOTE_COLOR_G_PAGE,    // LED 颜色R设置   (color 下子表单)
  REMOTE_COLOR_B_PAGE,    // LED 颜色R设置   (color 下子表单)


}OP_PAGE;



void Menu_Select_Item(menu_i32 current_index, button_status_e Key5Value , button_status_e Key0Value);

/******************* 进程处理 *********************/

void select_page_process(button_status_e Key5Value , button_status_e Key0Value);
void main_page_process(button_status_e Key5Value , button_status_e Key0Value);
void wifi_page_process(button_status_e Key5Value , button_status_e Key0Value);
void buletooth_page_process(button_status_e Key5Value, button_status_e Key0Value);
void wechat_page_process(button_status_e Key5Value, button_status_e Key0Value);
void remote_page_process(button_status_e Key5Value, button_status_e Key0Value);
void about_page_process(button_status_e Key5Value, button_status_e Key0Value);
void wifi_info_page_process(button_status_e Key5Value, button_status_e Key0Value);
void wifi_disconnect_page_process(button_status_e Key5Value, button_status_e Key0Value);
void wifi_smart_page_process(button_status_e Key5Value, button_status_e Key0Value);
void remote_color_page_process(button_status_e Key5Value, button_status_e Key0Value);
void remote_mode_page_process(button_status_e Key5Value, button_status_e Key0Value);
void remote_brigtness_page_process(button_status_e Key5Value, button_status_e Key0Value);
void remote_color_R_page_process(button_status_e Key5Value, button_status_e Key0Value);
void remote_color_G_page_process(button_status_e Key5Value, button_status_e Key0Value);
void remote_color_B_page_process(button_status_e Key5Value, button_status_e Key0Value);






void idle_page_process(button_status_e Key5Value , button_status_e Key0Value);



void Menu_Select_main(button_status_e Key5Value , button_status_e Key0Value);


uint8_t return_UI_loging_flag(void);
uint8_t return_flie_current_num(void);





#endif