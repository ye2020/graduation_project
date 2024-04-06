/**
  ****************************** Y.Z.T.****************************************
  * @file       menu.c/h
  * @brief      �ṩ��ֵ�����UI�˵��������
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
// ��Ӧ�������Ͷ���
typedef unsigned int   menu_u32;
typedef unsigned short menu_u16;
typedef unsigned char  menu_u8;

typedef int menu_i32 ;
typedef short menu_s16 ;
typedef char menu_s8 ;


// ��ֵ����ö��
typedef enum 
{
    KEY_none  = 0,
	  KEY_enter,          // ȷ��
    KEY_esc,            // ����
    KEY_up,             // ����
    KEY_dowm,           // ����
    KEY_home,           // home��
    KEY_setting,        // ���ü�

}key_value_e;

// �������������Ӳ˵�
typedef struct Menu_Key_Index
{
	menu_u8 main_current_index ;
	menu_u8 wifi_config_current_index ; 
  menu_u8 select_current_index;
  menu_u8 remote_current_index;
  menu_u8 color_current_index;
  menu_u8 mode_current_index;
  menu_u8 buletooth_current_index;

	menu_u8 Current_Page ;      // ��ǰҳ��
}Key_Index;


extern Key_Index sub_index ;

typedef void (*menu_op_func)(button_status_e , button_status_e);

typedef struct OP_STRUCT
{
	int op_menu ; 				//�����˵�
	menu_op_func opfun ;	//��������
}OP_MENU_PAGE;

/*��ǰ�˵�*/
typedef enum 
{
	MAIN_PAGE = 0,          // ��ҳ��						
  SELECT_PAGE,            // �˵�ҳ��   (1 ~ 10)����Ϊ�˵�ҳ�漰����ҳ��
  WiFi_PAGE,              // ��������ҳ��  (select ���ӱ���
  BULEBOOTH_PAGE,          // ����ҳ��    (select ���ӱ�)
  WECHAT_PAGE,            // ΢��С����ҳ��(select ���ӱ�)
  REMOTE_PAGE,            // ң��ҳ��      (select ���ӱ�)
  ABOUT_PAGE,             // �����豸      (select ���ӱ�)
  WIFI_INFO_PAGE = 11,    // ��ǰ������Ϣ    
  WIFI_DISCONNECT_PAGE,   // �Ͽ�����
  WIFI_SMART_CON_PAGE,    // ��������(ɨ��)
  REMOTE_PWOER_PAGE= 16,  // LED����
  REMOTE_COLOR_PAGE ,     // LED��ɫ����ҳ�� (remote ���ӱ�)
  REMOTE_MODE_PAGE,       // LEDģʽ����ҳ�� (remote ���ӱ�)
  REMOTE_BRIGHTNESS_PAGE, // LED��������ҳ�� (remote ���ӱ�)
  REMOTE_COLOR_R_PAGE= 21,// LED ��ɫR����   (color ���ӱ�)
  REMOTE_COLOR_G_PAGE,    // LED ��ɫR����   (color ���ӱ�)
  REMOTE_COLOR_B_PAGE,    // LED ��ɫR����   (color ���ӱ�)


}OP_PAGE;



void Menu_Select_Item(menu_i32 current_index, button_status_e Key5Value , button_status_e Key0Value);

/******************* ���̴��� *********************/

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