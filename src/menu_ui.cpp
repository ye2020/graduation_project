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
#include "usr_ws2812.h"

extern U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2;				// u8g2 库iic驱动

//主菜单初始化
void Menu_Main_Init(void)
{
	Serial.println("home status");

	sub_index.main_current_index = 0;
	sub_index.select_current_index = 2;				// 索引值2 ~ 10 留给 菜单表单及其子表单 
	sub_index.wifi_config_current_index = 11;		// 索引值11 ~ 15 留给网络配置页面
	sub_index.remote_current_index	= 16;			// 遥控索引16 ~ 25 留给遥控页面
	sub_index.color_current_index = 21;
	sub_index.mode_current_index = 0;				// 因为没有子页面, 所以无所谓
	sub_index.buletooth_current_index = 0;		


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

		// 进入LED亮度设置页面
	case REMOTE_COLOR_R_PAGE:
	{
		Menu_Select_Item(REMOTE_COLOR_R_PAGE, Key5Value,Key0Value);
		break;
	}

		// 进入LED亮度设置页面
	case REMOTE_COLOR_G_PAGE:
	{
		Menu_Select_Item(REMOTE_COLOR_G_PAGE, Key5Value,Key0Value);
		break;
	}

		// 进入LED亮度设置页面
	case REMOTE_COLOR_B_PAGE:
	{
		Menu_Select_Item(REMOTE_COLOR_B_PAGE, Key5Value,Key0Value);
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
void buletooth_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();	
	ui_show.menu_ui_show(ui_show.buletooth_list, 13, 9);	
	ui_show.progress_ui_show(ui_show.buletooth_line_len, ui_show.buletooth_single_line_length, 5);      // 进度条UI绘制				
	u8g2.sendBuffer();
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


// 颜色设置页面页面UI进程
void led_color_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();
	ui_show.menu_ui_show(ui_show.color_list, 13, 9);	
	ui_show.progress_ui_show(ui_show.color_line_len, ui_show.color_single_line_length, 10);      // 进度条UI绘制			
	u8g2.sendBuffer();	
}


// 模式设置页面页面UI进程
void led_mode_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();
	ui_show.menu_ui_show(ui_show.mode_list, 13, 9);	
	ui_show.progress_ui_show(ui_show.mode_line_len, ui_show.mode_single_line_length, 5);      // 进度条UI绘制		
	u8g2.sendBuffer();
}

// 亮度设置页面页面UI进程
void led_brightness_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();

	u8g2.drawStr(3, 60, "0");
	u8g2.drawStr(110, 60, "150");
	u8g2.drawStr(20, 30, "Brightness: ");
	u8g2.setCursor(85, 30);
    u8g2.print(ws_led.Brightness);

    (ws_led.Brightness < 150) ? (ui_show.horizontal_progress_len_brightness.position_trg = (ws_led.Brightness/15)*10) : (ui_show.horizontal_progress_len_B.position_trg = 100);
	ui_show.Horizontal_progress_ui_show(&ui_show.horizontal_progress_len_brightness.cur_position, &ui_show.horizontal_progress_len_brightness.position_trg, 8);			// 绘制横向进度条
	u8g2.sendBuffer();
}

// 颜色R设置页面UI进程
void color_R_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();

	u8g2.drawStr(3, 60, "0");
	u8g2.drawStr(110, 60, "255");
	u8g2.drawStr(45, 30, "R :");
	u8g2.setCursor(65, 30);
    u8g2.print(ws_led.color_R);

	(ws_led.color_R < 255) ? (ui_show.horizontal_progress_len.position_trg = (ws_led.color_R/25)*10) : (ui_show.horizontal_progress_len.position_trg = 100);
	ui_show.Horizontal_progress_ui_show(&ui_show.horizontal_progress_len.cur_position, &ui_show.horizontal_progress_len.position_trg, 8);			// 绘制横向进度条
	u8g2.sendBuffer();
}

// 颜色G设置页面UI进程
void color_G_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();

	u8g2.drawStr(3, 60, "0");
	u8g2.drawStr(110, 60, "255");
	u8g2.drawStr(45, 30, "G :");
	u8g2.setCursor(65, 30);
    u8g2.print(ws_led.color_G);

    (ws_led.color_G < 255) ? (ui_show.horizontal_progress_len_G.position_trg = (ws_led.color_G/25)*10) : (ui_show.horizontal_progress_len_G.position_trg = 100);
	ui_show.Horizontal_progress_ui_show(&ui_show.horizontal_progress_len_G.cur_position, &ui_show.horizontal_progress_len_G.position_trg, 8);			// 绘制横向进度条
	u8g2.sendBuffer();
}



// 颜色B设置页面UI进程
void color_B_ui_process(void)
{
	u8g2.clearBuffer();	
	top_ui_show();

	u8g2.drawStr(3, 60, "0");
	u8g2.drawStr(110, 60, "255");
	u8g2.drawStr(45, 30, "B :");
	u8g2.setCursor(65, 30);
    u8g2.print(ws_led.color_B);

    (ws_led.color_B < 255) ? (ui_show.horizontal_progress_len_B.position_trg = (ws_led.color_B/25)*10) : (ui_show.horizontal_progress_len_B.position_trg = 100);
	ui_show.Horizontal_progress_ui_show(&ui_show.horizontal_progress_len_B.cur_position, &ui_show.horizontal_progress_len_B.position_trg, 8);			// 绘制横向进度条
	u8g2.sendBuffer();
}