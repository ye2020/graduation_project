/**
  ****************************** Y.Z.T.****************************************
  * @file       menu_ui.c/h
  * @brief      提供菜单框架中UI的处理，储存UI绘制的进程函数
  * @note
  * @history    2022.7.8
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
#include "menu_ui.h"
#include "usr_ui_show.h"


extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;				// u8g2 库iic驱动

//主菜单初始化
void Menu_Main_Init(void)
{
	Serial.println("home status");

	sub_index.main_current_index = 0;
	sub_index.select_current_index = 2;				// 索引值2 ~ 10 留给 菜单表单及其子表单 
	//sub_index.wifi_config_current_index = 2;
			


	sub_index.Current_Page = MAIN_PAGE;					// 设置初始页面

}

//进入相应的页面
void Enter_Page(menu_i32 index, button_status_e Key5Value , button_status_e Key0Value)
{
	
	sub_index.Current_Page = index;
	switch (sub_index.Current_Page)
	{
		//进入主页面
	case MAIN_PAGE:
	{
		Menu_Select_Item(MAIN_PAGE, Key5Value,Key0Value);
		break;
	}
	//进入wifi配网页面
	case WiFi_PAGE:
	{
		Menu_Select_Item(WiFi_PAGE,  Key5Value,Key0Value);
		break;
	}

	//进入菜单页面
	case SELECT_PAGE:
	{
		Menu_Select_Item(SELECT_PAGE,  Key5Value,Key0Value);
		break;
	}

	// 否则返回主页面
	default:
	{	Menu_Select_Item(MAIN_PAGE, Key5Value,Key0Value);
		break;
	}
	}
}

//主页面UI处理
void main_page_ui_process(void)
{

	u8g2.clearBuffer();	
	top_ui_show();							
	u8g2.drawXBMP(40,16,50,50,ACE);				// LOGO 绘制
	u8g2.sendBuffer();
}


// 菜单页面ui进程
void select_page_ui_process(void)
{
	u8g2.clearBuffer();             // 清除缓存
	top_ui_show();					// 表头常驻UI
	ui_show.menu_ui_show(ui_show.list);			// 绘制菜单
	u8g2.sendBuffer();              // 将缓存发送并显示
}


// wifi设置页面UI进程
void wifi_page_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();							
	u8g2.drawXBMP(40,16,50,50,QR_code_50_50);				// LOGO 绘制
	u8g2.sendBuffer();
}

