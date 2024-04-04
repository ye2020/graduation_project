/**
  ****************************** Y.Z.T.****************************************
  * @file       menu_ui.c/h
  * @brief      提供菜单框架中UI的处理，储存UI绘制的进程函数
  * @note
  * @history    2023.9.20
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
#include "menu_ui.h"
#include "usr_ui_show.h"
#include "usr_wifi.h"
#include "usr_dht.h"

extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;				// u8g2 库iic驱动

//主菜单初始化
void Menu_Main_Init(void)
{
	Serial.println("home status");

	sub_index.main_current_index = 0;
	sub_index.select_current_index = 2;				// 索引值2 ~ 10 留给 菜单表单及其子表单 
	sub_index.wifi_config_current_index = 11;		// 索引值11 ~ 15 留给网络配置页面
	sub_index.remote_current_index	= 16;			// 遥控索引16 ~ 25 留给遥控页面
			


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

	//进入蓝牙页面
	case BULEBOOTH_PAGE:
	{
		Menu_Select_Item(BULEBOOTH_PAGE,  Key5Value,Key0Value);
		break;
	}

		//进入LED设置页面
	case REMOTE_PAGE:
	{
		Menu_Select_Item(REMOTE_PAGE,  Key5Value,Key0Value);
		break;
	}

		//进入微信小程序页面
	case WECHAT_PAGE:
	{
		Menu_Select_Item(WECHAT_PAGE,  Key5Value,Key0Value);
		break;
	}

		//进入菜单页面
	case IR_CHECK_PAGE:
	{
		Menu_Select_Item(IR_CHECK_PAGE,  Key5Value,Key0Value);
		break;
	}

		//进入菜单页面
	case ABOUT_PAGE:
	{
		Menu_Select_Item(ABOUT_PAGE,  Key5Value,Key0Value);
		break;
	}

		//进入网络信息页面
	case WIFI_INFO_PAGE:
	{
		Menu_Select_Item(WIFI_INFO_PAGE,  Key5Value,Key0Value);
		break;
	}

		//进入断开连接页面
	case WIFI_DISCONNECT_PAGE:
	{
		Menu_Select_Item(WIFI_DISCONNECT_PAGE,  Key5Value,Key0Value);
		break;
	}

		//进入配网页面
	case WIFI_SMART_CON_PAGE:
	{
		Menu_Select_Item(WIFI_SMART_CON_PAGE,  Key5Value,Key0Value);
		break;
	}

	// 进入LED开关页面
	case REMOTE_PWOER_PAGE:
	{
		Menu_Select_Item(MAIN_PAGE, Key5Value,Key0Value);
		break;
	}

	// 进入LED颜色页面
	case REMOTE_COLOR_PAGE:
	{
		Menu_Select_Item(REMOTE_COLOR_PAGE, Key5Value,Key0Value);
		break;
	}

	// 进入LED模式设置页面
	case REMOTE_MODE_PAGE:
	{
		Menu_Select_Item(REMOTE_MODE_PAGE, Key5Value,Key0Value);
		break;
	}

	// 进入LED亮度设置页面
	case REMOTE_BRIGHTNESS_PAGE:
	{
		Menu_Select_Item(REMOTE_BRIGHTNESS_PAGE, Key5Value,Key0Value);
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
	u8g2.clearBuffer();             														 // 清除缓存
	top_ui_show();																			 // 表头常驻UI
	ui_show.menu_ui_show(ui_show.list, 13, 9);														 // 绘制菜单
	ui_show.progress_ui_show(ui_show.line_len, ui_show.single_line_length, 4);                  // 进度条UI绘制
	u8g2.sendBuffer();              														 // 将缓存发送并显示
}


// wifi设置页面UI进程
void wifi_page_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();
	ui_show.menu_ui_show(ui_show.wifi_list, 13, 9);	
	ui_show.progress_ui_show(ui_show.wifi_line_len, ui_show.wifi_single_line_length, 4);      // 进度条UI绘制						
	u8g2.sendBuffer();
}

// 遥控页面UI进程
void remote_page_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();
	ui_show.menu_ui_show(ui_show.remote_list, 13, 9);	
	ui_show.progress_ui_show(ui_show.remote_line_len, ui_show.remote_single_line_length, 10);      // 进度条UI绘制			
	u8g2.sendBuffer();	
}

// 扫码配网页面UI进程
void wifi_smart_conf_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();	
	u8g2.drawXBMP(40,16,50,50,QR_code_50_50);				// 二维码 绘制
	u8g2.sendBuffer();
}


// 断开页面UI进程
void wifi_discon_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();	
	u8g2.drawUTF8(20,35,"网络已断开 ");
    u8g2.drawUTF8(20,50,"点击任意键退出...");
	u8g2.sendBuffer();
}


// wifi信息页面UI进程
void wifi_info_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();

	if(WiFi.status() != WL_CONNECTED)				// 当前无网络连接
	{
		u8g2.drawUTF8(20,35,"网络已断开 ");
    	u8g2.drawUTF8(20,50,"点击任意键快速连接");
	}				
	else 
	{
		u8g2.drawStr(3, 30, "SSID :");
		u8g2.setCursor(40, 30);
    	u8g2.print(usr_Wifi.return_SSID());
		u8g2.drawStr(3, 45, "IP   :");
		u8g2.setCursor(40, 45);
    	u8g2.print(usr_Wifi.return_IP_addr());
		u8g2.drawStr(3, 60, "MAC :");
		u8g2.setCursor(40, 60);
    	u8g2.print(usr_Wifi.return_MAC());		
	}

	u8g2.sendBuffer();
}


// 温湿度页面UI进程
void temp_hum_ui_process(void)
{
	// u8g2.clearBuffer();	
	// top_ui_show();
	// u8g2.drawUTF8(3, 30, "温度 :");
	// u8g2.setCursor(40, 30);
    // u8g2.print(usr_dht.temp);
	// u8g2.drawStr(74, 28, "*C");
	// u8g2.drawUTF8(3, 55, "湿度 :");
	// u8g2.setCursor(40, 55);
    // u8g2.print(usr_dht.Hum);
	// u8g2.drawStr(74, 53, "%");
	// u8g2.sendBuffer();
}

// 小程序页面UI进程
void wechat_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();	
	u8g2.drawXBMP(40,16,50,50,QR_wechat_50_50);				// 二维码 绘制
	u8g2.sendBuffer();
}

// 设备信息页面UI进程
void about_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();
	u8g2.drawStr(3, 30, "MCU   :  ESP8266");
	u8g2.drawStr(3, 45, "Flash  :  1MB");
	u8g2.drawStr(3, 60, "SRAM  :  80KB");
	u8g2.sendBuffer();
}


// 红外检测页面UI进程
void ir_check_ui_process(bool status)
{
	// u8g2.clearBuffer();	
	// top_ui_show();
	// if(status)
	// {
	// 	u8g2.drawXBMP(40,16,50,47,ir_check_50_47);
	// }
	// else
	// {
	// 	// u8g2.drawUTF8(35, 48, "未检测到...");
	// 	u8g2.drawXBMP(40,16,50,47,ir_fail_50_47);
	// }
	// u8g2.sendBuffer();
}