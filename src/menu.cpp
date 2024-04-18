/**
  ****************************** Y.Z.T.****************************************
  * @file       menu.c/h
  * @brief      提供键值适配等UI菜单框架数据
  * @note       框架移植自STM32工程，因项目UI子菜单仅2层，有些函数不是很必要，故稍显臃肿和混乱
  * @history    2023.9.20
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
/***************************** 操作说明 ******************************
 * 	
 * 		操作说明：
 * 			左键（key5）：
 * 				单击：向下选择 （在主页进入菜单页面）	
 * 				双击：确认enter
 * 				长按：主页进入设置模式
 * 			
 *			右键（key0）: 
 * 				单击：向上选择
 * 				双击：返回esc
 * 				长按：返回主页home
 * 
 * 		特别注意：两键不可同时按，同时按返回无指令
*******************************************************************/


#include "menu.h"
#include <Arduino.h>
#include "usr_ui_show.h"
#include "menu_ui.h"
#include "usr_wifi.h"
#include "usr_clock_time.h"
#include "usr_dht.h"
#include "usr_SR505.h"
#include "usr_irremote.h"
#include "usr_ws2812.h"


// 定义菜单索引变量
Key_Index sub_index;
uint8_t  page_current_sta = 1;		//当前页码
static uint8_t flie_current_num = 0;		// 当前书籍编号

static key_value_e Key5Value_transition_function(button_status_e button5, button_status_e button0);
void Menu_Select_Item(menu_i32 current_index, button_status_e Key5Value, button_status_e Key0Value);
uint8_t ui_loging_flag = 0;				//将ui加载标志位置0，表示允许加载ui


//菜单操作表定义
static OP_MENU_PAGE g_opStruct[] =
	{
		{MAIN_PAGE, main_page_process},
		{SELECT_PAGE, select_page_process},
		{WiFi_PAGE, wifi_page_process},
		{BULEBOOTH_PAGE, buletooth_page_process},
		{REMOTE_PAGE, remote_page_process},
		{ABOUT_PAGE, about_page_process},
		{6,idle_page_process},
		{7,idle_page_process},
		{8,idle_page_process},										// 留空
		{9,idle_page_process},										// 留空
		{10,idle_page_process},										// 留空
		{WIFI_INFO_PAGE, wifi_info_page_process},
		{WIFI_DISCONNECT_PAGE, wifi_disconnect_page_process},
		{WIFI_SMART_CON_PAGE, wifi_smart_page_process},
		{14, idle_page_process},
		{15, idle_page_process},
		{16, idle_page_process},
		{REMOTE_COLOR_PAGE, remote_color_page_process},
		{REMOTE_MODE_PAGE, remote_mode_page_process},
		{REMOTE_BRIGHTNESS_PAGE, remote_brigtness_page_process},
		{20, idle_page_process},
		{REMOTE_COLOR_R_PAGE, remote_color_R_page_process},
		{REMOTE_COLOR_G_PAGE, remote_color_G_page_process},
		{REMOTE_COLOR_B_PAGE, remote_color_B_page_process}
	};


//跳转到表所对应的页面
static int JUMP_Table(menu_u32 op, button_status_e Key5Value, button_status_e Key0Value)
{
	if (op >= sizeof(g_opStruct) / sizeof(g_opStruct[0]) || op < 0) // 判断该页面是否在表内（1~ 7 ）
	{
		Serial.println("unknow operate!");
		return -1;
	}
	g_opStruct[op].opfun(Key5Value, Key0Value); // 执行操作
	return 0;
}

//菜单选择项
void Menu_Select_Item(menu_i32 current_index, button_status_e Key5Value, button_status_e Key0Value)
{
	JUMP_Table(current_index, Key5Value, Key0Value);
}

/**
 * @brief
 * @param[in]   Key5Value ： 左键key5键值（左） ； Key0Value（右）
 * @retval      在loop函数调用
 * @attention
 */
void Menu_Select_main(button_status_e Key5Value, button_status_e Key0Value)
{
	Enter_Page(sub_index.Current_Page, Key5Value, Key0Value);
}

/**
 * @brief		返回当前阅读的书籍编号
 * @param[in]   none
 * @retval      none
 * @attention
 */
uint8_t return_flie_current_num(void)
{
	return flie_current_num;
}

/**
 * @brief       左键值转换，从具体的按键如（单击，双击转换成每个页面的对应功能）
 * @param[in]   button5 (左)
 * @retval
 * @attention
 */
static key_value_e Key5Value_transition_function(button_status_e button5, button_status_e button0)
{
	button_status_e button_CS = button_none;

	if		(button5 != button_none && button0 == button_none) 		button_CS = button5;
	else if (button5 == button_none && button0 != button_none)		button_CS = button0;
	else															button_CS = button_none;

	switch (button_CS)
	{

	/**************** 左按键对应键值 *******************/
	// key5 短按一下向下
	case button_click:
	{
		Serial.println("KEY_dowm");		
		return KEY_dowm;
		break;
	}
	// key5 长按确定
	case button_longPressStart:
	{
		Serial.println("KEY_enter");		
		return KEY_enter;
		break;
	}

	// // key5 长按进入设置模式
	// case button_longPressStop:
	// {
	// 	Serial.println("KEY_setting");		
	// 	return KEY_setting;
	// 	break;
	// }

	/**************** 右按键对应键值 *******************/

	// key0 长按返回上一级
	case button_longPressStart2:
	{
		Serial.println("KEY_esc");		
		return KEY_esc;
		break;
	}

	// key0 短按向上
	case button_click2:
	{
		Serial.println("KEY_up");		
		return KEY_up;
		break;
	}

	// key0 短按2下home键 (只在蓝牙有效)
	case button_doubleclick2:
	{
		Serial.println("KEY_home");		
		return KEY_home;
		break;
	}
	default:
		break;
	}

	return KEY_none;
}



/**
 * @brief		复位索引和选择框进度条的位置
 * @param[in]   status: 进入新的页面是为ture;  退回上级时为false
 * 				len   : 新的页面第一项的选择框长度
 * @retval      none
 * @attention
 */
void index_reset(bool status, int16_t len)
{
	if(status == false) 
	{
		sub_index.main_current_index = 0;
		sub_index.select_current_index = 2;				// 索引值2 ~ 10 留给 菜单表单及其子表单 
		sub_index.wifi_config_current_index = 11;		// 索引值11 ~ 15 留给网络配置页面
		sub_index.remote_current_index = 16;
		sub_index.color_current_index = 21;
		sub_index.mode_current_index = 0;
		sub_index.buletooth_current_index = 0;
	}
	ui_show.frame_len = {len, len};																// 复位选择框
	ui_show.frame_y	  = {17, 17};
	ui_show.progress_position = {16, 16};														// 复位进度条
	ui_show.text_bottom_index = 2;
	ui_show.text_top_index = 0;
}

uint8_t return_UI_loging_flag(void)
{
	return ui_loging_flag;
}

/************************************************************************************************************************************/
/*********************************************************** 进程处理 **********************************************************/
/************************************************************************************************************************************/

/**
 * @brief       主页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void main_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	main_page_ui_process();					// 主页面ui绘制
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{
		ui_show.ui_disapper();								// 消失函数
		Enter_Page(SELECT_PAGE, Key5Value, Key0Value);		// 进入选择页面
		break;
	}

	case KEY_up:
	{
		ui_show.ui_disapper();								// 消失函数
		Enter_Page(SELECT_PAGE, Key5Value, Key0Value);		// 进入选择页面
		break ;
	}

	case KEY_enter:
	{

		break;
	}

	case KEY_home:
	{

		break;
	}

	case KEY_esc:
	{	

		break;
	}
	default:
		break;
	}
}

/**
 * @brief       菜单页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void select_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	// Serial.println("select status");

	select_page_ui_process();	
										// 菜单页面ui绘制
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{
		// 临界条件判断
		(sub_index.select_current_index < (2 + ui_show.line_len - 1)) ? (sub_index.select_current_index++) : (sub_index.select_current_index = (2 + ui_show.line_len - 1));

		// 进度条目标位置
		if(ui_show.progress_position.position_trg < (ui_show.max_bar - ui_show.single_line_length -  1))  {
			(ui_show.progress_position.position_trg += ui_show.single_line_length);
		}
		
		// ui_show.frame_y.position_trg    =  (sub_index.select_current_index  - 2)* 11 + (ui_show.y_offset + 2);								 // 选择框位置目标值
		
		// 当前指向的页面在屏幕外面
		if((sub_index.select_current_index - 2) > (ui_show.text_bottom_index))
		{
			// ui_show.menu_y_position.position_trg -= 11;					// 上移菜单 
			ui_show.text_bottom_index += 1;								// 更新索引
			ui_show.text_top_index = ui_show.text_bottom_index - 2;
		} 
		else 
		{
			ui_show.frame_y.position_trg += 15;							// 下移框
			Serial.println("y.position_trg");
			Serial.println(ui_show.frame_y.position_trg);		
			
		}

		(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);  // 选择框位置限制
		(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);
  		
		ui_show.frame_len.position_trg  =  ui_show.list[sub_index.select_current_index - 2].len * 5;

		Serial.println("down to choose");
		Serial.println(sub_index.select_current_index);		
		break;
	}

	case KEY_up:
	{
		(sub_index.select_current_index > 2) ? (sub_index.select_current_index--) : (sub_index.select_current_index = 2);

		// 进度条目标位置
		if(ui_show.progress_position.position_trg > (ui_show.single_line_length + ui_show.y_offset - 2))  {
			(ui_show.progress_position.position_trg -= ui_show.single_line_length);
		}


		// 当前指向的页面在屏幕外面
		if((sub_index.select_current_index - 2) < (ui_show.text_top_index))
		{
			// ui_show.menu_y_position.position_trg += 11;					// 下移菜单 
			ui_show.text_top_index -= 1;
			ui_show.text_bottom_index = ui_show.text_top_index + 2;
		} 
		else 
		{
			ui_show.frame_y.position_trg -= 15;							// 上移框
		}	

		(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);	// 选择框位置限制
		(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);

  		ui_show.frame_len.position_trg  =  ui_show.list[sub_index.select_current_index - 2].len * 5;		

		Serial.println("down to choose");
		Serial.println(sub_index.select_current_index);		
		break ;
	}
	case KEY_enter:
	{
		Serial.println("Enter the choice");
		Serial.println((sub_index.select_current_index));

		index_reset(true, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page((sub_index.select_current_index ), button_none, button_none);					// 页面跳转
		break;
	}

	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数											
		Enter_Page(MAIN_PAGE,button_none,button_none);												// home键返回主页面
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数	
		Enter_Page(MAIN_PAGE,button_none,button_none);												// 返回上级页面 即main
		break;
	}
	default:
		break;
	}
}

/**
 * @brief       wifi设置页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void wifi_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	// Serial.println("wifi status");
	wifi_page_ui_process();												// ui绘制
	/*************************** 键值处理 **************************/
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{
		// 临界条件判断
		(sub_index.wifi_config_current_index < (11 + ui_show.wifi_line_len - 1)) ? (sub_index.wifi_config_current_index++) : (sub_index.wifi_config_current_index = (11 + ui_show.wifi_line_len - 1));
		
		// 进度条目标位置
		if(ui_show.progress_position.position_trg < (ui_show.max_bar - ui_show.wifi_single_line_length -  1))  {
			(ui_show.progress_position.position_trg += ui_show.wifi_single_line_length);
		}
	
		{
			ui_show.frame_y.position_trg += 15;							// 下移框
			Serial.println("y.position_trg");
			Serial.println(ui_show.frame_y.position_trg);		
			
		}

		(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);  // 选择框位置限制
		(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);
  		
		ui_show.frame_len.position_trg  =  ui_show.wifi_list[sub_index.wifi_config_current_index - 11].len * 5;

		Serial.println("down to choose");
		Serial.println(sub_index.wifi_config_current_index);		
		break;		

	}

	case KEY_up:
	{
		(sub_index.wifi_config_current_index > 11) ? (sub_index.wifi_config_current_index--) : (sub_index.wifi_config_current_index = 11);

		// 进度条目标位置
		if(ui_show.progress_position.position_trg > (ui_show.wifi_single_line_length + ui_show.y_offset - 2))  {
			(ui_show.progress_position.position_trg -= ui_show.wifi_single_line_length);
		}

		{
			ui_show.frame_y.position_trg -= 15;							// 上移框
		}	

		(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);	// 选择框位置限制
		(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);

  		ui_show.frame_len.position_trg  =  ui_show.wifi_list[sub_index.wifi_config_current_index - 11].len * 5;		

		Serial.println("down to choose");
		Serial.println(sub_index.wifi_config_current_index);		
		break ;
	}
	case KEY_enter:
	{
		index_reset(true, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Serial.println("Enter the choice");
		Serial.println((sub_index.wifi_config_current_index));																
		Enter_Page((sub_index.wifi_config_current_index ), button_none, button_none);				// 页面跳转
		break;
	}

	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);												// home键返回主页面
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(SELECT_PAGE,button_none,button_none);											// 返回选择页面
		break;
	}
	default:
		break;
	}
}


/**
 * @brief      	温湿度页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void buletooth_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	// Serial.println("temp status");
	buletooth_ui_process();

	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{
			// 临界条件判断
			(sub_index.buletooth_current_index < (ui_show.buletooth_line_len - 1)) ? (sub_index.buletooth_current_index++) : (sub_index.buletooth_current_index = (ui_show.buletooth_line_len - 1));
			
			// 进度条目标位置
			if(ui_show.progress_position.position_trg < (ui_show.max_bar - ui_show.buletooth_single_line_length -  1))  {
				(ui_show.progress_position.position_trg += ui_show.buletooth_single_line_length);
			}
		
			ui_show.frame_y.position_trg += 15;							// 下移框
			Serial.println("y.position_trg");
			Serial.println(ui_show.frame_y.position_trg);		

			(ui_show.frame_y.position_trg < (ui_show.screen_height - 20)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 32);  // 选择框位置限制
			(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);
			
			ui_show.frame_len.position_trg  =  ui_show.buletooth_list[sub_index.buletooth_current_index].len * 5;

			Serial.println("down to choose");
			Serial.println(sub_index.buletooth_current_index);		
			break;					
		}

	case KEY_up:
	{
			(sub_index.buletooth_current_index > 0) ? (sub_index.buletooth_current_index--) : (sub_index.buletooth_current_index = 0);

			// 进度条目标位置
			if(ui_show.progress_position.position_trg > (ui_show.buletooth_single_line_length + ui_show.y_offset - 2))  {
				(ui_show.progress_position.position_trg -= ui_show.buletooth_single_line_length);
			}


			ui_show.frame_y.position_trg -= 15;							// 上移框


			(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);	// 选择框位置限制
			(ui_show.frame_y.position_trg < (ui_show.screen_height - 20)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 32);

			ui_show.frame_len.position_trg  =  ui_show.buletooth_list[sub_index.buletooth_current_index].len * 5;		

			Serial.println("down to choose");
			Serial.println(sub_index.buletooth_current_index);		
			break ;
	}

	case KEY_enter:
	{
		if(sub_index.buletooth_current_index == 0){
			buletooth_on();
		}else {
			buletooth_off();
		}

		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(SELECT_PAGE,button_none,button_none);
		break;
	}

	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(SELECT_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}


/**
 * @brief      	微信小程序页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void wechat_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	// Serial.println("wechat status");
	wechat_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(SELECT_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}

/**
 * @brief      	遥控页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void remote_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	remote_page_ui_process(); 

	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
		case KEY_dowm:
		{
			// 临界条件判断
			(sub_index.remote_current_index < (16 + ui_show.remote_line_len - 1)) ? (sub_index.remote_current_index++) : (sub_index.remote_current_index = (16 + ui_show.remote_line_len - 1));
			
			// 进度条目标位置
			if(ui_show.progress_position.position_trg < (ui_show.max_bar - ui_show.remote_single_line_length -  1))  {
				(ui_show.progress_position.position_trg += ui_show.remote_single_line_length);
			}
		

			// 当前指向的页面在屏幕外面
			if((sub_index.remote_current_index - 16) > (ui_show.text_bottom_index))
			{
				ui_show.text_bottom_index += 1;								// 更新索引
				ui_show.text_top_index = ui_show.text_bottom_index - 2;
			}
			else
			{
				ui_show.frame_y.position_trg += 15;							// 下移框
				Serial.println("y.position_trg");
				Serial.println(ui_show.frame_y.position_trg);		
				
			}

			(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);  // 选择框位置限制
			(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);
			
			ui_show.frame_len.position_trg  =  ui_show.remote_list[sub_index.remote_current_index - 16].len * 5;

			Serial.println("down to choose");
			Serial.println(sub_index.remote_current_index);		
			break;					
		}

		case KEY_up:
		{
			(sub_index.remote_current_index > 16) ? (sub_index.remote_current_index--) : (sub_index.remote_current_index = 16);

			// 进度条目标位置
			if(ui_show.progress_position.position_trg > (ui_show.remote_single_line_length + ui_show.y_offset - 2))  {
				(ui_show.progress_position.position_trg -= ui_show.remote_single_line_length);
			}

			if((sub_index.remote_current_index - 16) < (ui_show.text_top_index))
			{
				// ui_show.menu_y_position.position_trg += 11;					// 下移菜单 
				ui_show.text_top_index -= 1;
				ui_show.text_bottom_index = ui_show.text_top_index + 2;
			}
			else 
			{
				ui_show.frame_y.position_trg -= 15;							// 上移框
			}	

			(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);	// 选择框位置限制
			(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);

			ui_show.frame_len.position_trg  =  ui_show.remote_list[sub_index.remote_current_index - 16].len * 5;		

			Serial.println("down to choose");
			Serial.println(sub_index.remote_current_index);		
			break ;
		}

		case KEY_enter:
		{
			Serial.println("Enter the choice");
			Serial.println((sub_index.remote_current_index));

			index_reset(true, 55);																		// 复位选择框与进度条
			ui_show.ui_disapper();																		// 消失函数

			if(sub_index.remote_current_index == REMOTE_PWOER_PAGE){									// 如果是开关选项, 则只运行对应回调函数, 而不进入对应表单
				ws2812_power_callback();
			}
			else{
				Enter_Page((sub_index.remote_current_index ), button_none, button_none);					// 页面跳转
			}
			
			break;
		}

		case KEY_home:
		{
			index_reset(false, 55);																		// 复位选择框与进度条
			ui_show.ui_disapper();																		// 消失函数	
			Enter_Page(MAIN_PAGE,button_none,button_none);												// 返回上级页面 即main
			break;
		}

		case KEY_esc:
		{
			index_reset(false, 55);																		// 复位选择框与进度条
			ui_show.ui_disapper();																		// 消失函数	
			Enter_Page(SELECT_PAGE,button_none,button_none);												// 返回上级页面 即main
			break;
		}

		default:
		break;
	}
}



/**
 * @brief      	关于设备页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void about_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	// Serial.println("about status");
	about_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(SELECT_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}



/**
 * @brief      	网络信息页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void wifi_info_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	// Serial.println("wifi_info status");
	wifi_info_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{
		usr_Wifi.wifi_quick_link();								//快速连接
		break;
	}

	case KEY_up:
	{
		usr_Wifi.wifi_quick_link();								//快速连接
		break ;
	}
	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(WiFi_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}


/**
 * @brief      	断开网络页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void wifi_disconnect_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	// Serial.println("wifi_disconnect status");
	usr_Wifi.wifi_disconnect();										// 断开网络
	wifi_discon_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();		
		Enter_Page(WiFi_PAGE,button_none,button_none);
		break;
	}

	case KEY_up:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();		
		Enter_Page(WiFi_PAGE,button_none,button_none);
		break ;
	}

	case KEY_enter:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();		
		Enter_Page(WiFi_PAGE,button_none,button_none);
		break;
	}
	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(WiFi_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}


/**
 * @brief      	扫码配网页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void wifi_smart_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	// Serial.println("wifi_smart status");
	wifi_smart_conf_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{
		usr_Wifi.wifi_smartconfig();
		clock_updata();               													     		//更新时间数据
		break;
	}
	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(WiFi_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}


/**
 * @brief      	LED 颜色设置页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void remote_color_page_process(button_status_e Key5Value, button_status_e Key0Value)
{

	led_color_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{
			// 临界条件判断
			(sub_index.color_current_index < (21 + ui_show.color_line_len - 1)) ? (sub_index.color_current_index++) : (sub_index.color_current_index = (21 + ui_show.color_line_len - 1));
			
			// 进度条目标位置
			if(ui_show.progress_position.position_trg < (ui_show.max_bar - ui_show.color_single_line_length -  1))  {
				(ui_show.progress_position.position_trg += ui_show.color_single_line_length);
			}
		
			ui_show.frame_y.position_trg += 15;							// 下移框
			Serial.println("y.position_trg");
			Serial.println(ui_show.frame_y.position_trg);		

			(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);  // 选择框位置限制
			(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);
			
			ui_show.frame_len.position_trg  =  ui_show.color_list[sub_index.color_current_index - 21].len * 5;

			Serial.println("down to choose");
			Serial.println(sub_index.color_current_index);		
			break;					
		}

	case KEY_up:
	{
			(sub_index.color_current_index > 21) ? (sub_index.color_current_index--) : (sub_index.color_current_index = 21);

			// 进度条目标位置
			if(ui_show.progress_position.position_trg > (ui_show.color_single_line_length + ui_show.y_offset - 2))  {
				(ui_show.progress_position.position_trg -= ui_show.color_single_line_length);
			}


			ui_show.frame_y.position_trg -= 15;							// 上移框


			(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);	// 选择框位置限制
			(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);

			ui_show.frame_len.position_trg  =  ui_show.color_list[sub_index.color_current_index - 21].len * 5;		

			Serial.println("down to choose");
			Serial.println(sub_index.color_current_index);		
			break ;
	}

	case KEY_enter:
	{
		Serial.println("Enter the choice");
		Serial.println((sub_index.color_current_index));

		index_reset(true, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page((sub_index.color_current_index ),button_none,button_none);
		break;
	}
	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(REMOTE_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}



/**
 * @brief      	LED 模式设置页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void remote_mode_page_process(button_status_e Key5Value, button_status_e Key0Value)
{

	led_mode_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{
			// 临界条件判断
			(sub_index.mode_current_index < (ui_show.mode_line_len - 1)) ? (sub_index.mode_current_index++) : (sub_index.mode_current_index = (ui_show.mode_line_len - 1));
			
			// 进度条目标位置
			if(ui_show.progress_position.position_trg < (ui_show.max_bar - ui_show.mode_single_line_length -  1))  {
				(ui_show.progress_position.position_trg += ui_show.mode_single_line_length);
			}
		

			// 当前指向的页面在屏幕外面
			if((sub_index.mode_current_index) > (ui_show.text_bottom_index))
			{
				ui_show.text_bottom_index += 1;								// 更新索引
				ui_show.text_top_index = ui_show.text_bottom_index - 2;
			}
			else
			{
				ui_show.frame_y.position_trg += 15;							// 下移框
				Serial.println("y.position_trg");
				Serial.println(ui_show.frame_y.position_trg);		
				
			}

			(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);  // 选择框位置限制
			(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);
			
			ui_show.frame_len.position_trg  =  ui_show.mode_list[sub_index.mode_current_index].len * 5;

			Serial.println("down to choose");
			Serial.println(sub_index.mode_current_index);		
			break;					
	}

	case KEY_up:
	{
			(sub_index.mode_current_index > 0) ? (sub_index.mode_current_index--) : (sub_index.mode_current_index = 0);

			// 进度条目标位置
			if(ui_show.progress_position.position_trg > (ui_show.mode_single_line_length + ui_show.y_offset - 2))  {
				(ui_show.progress_position.position_trg -= ui_show.mode_single_line_length);
			}

			if((sub_index.mode_current_index) < (ui_show.text_top_index))
			{
				// ui_show.menu_y_position.position_trg += 11;					// 下移菜单 
				ui_show.text_top_index -= 1;
				ui_show.text_bottom_index = ui_show.text_top_index + 2;
			}
			else 
			{
				ui_show.frame_y.position_trg -= 15;							// 上移框
			}	

			(ui_show.frame_y.position_trg > ui_show.y_offset) ? (ui_show.frame_y.position_trg -= 0) : (ui_show.frame_y.position_trg = 18);	// 选择框位置限制
			(ui_show.frame_y.position_trg < (ui_show.screen_height - 5)) ? (ui_show.frame_y.position_trg += 0) : (ui_show.frame_y.position_trg = 47);

			ui_show.frame_len.position_trg  =  ui_show.mode_list[sub_index.mode_current_index].len * 5;		

			Serial.println("down to choose");
			Serial.println(sub_index.mode_current_index);		
			break ;
	}

	case KEY_enter:
	{
		ws_led.LED_mode = (WS_LED_mode_e)sub_index.mode_current_index;
		ws_led.ws2812_setting(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color);				// 写入rom
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();		
		Enter_Page(REMOTE_PAGE,button_none,button_none);
		break;
	}
	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(REMOTE_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}



/**
 * @brief      	LED 亮度设置页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void remote_brigtness_page_process(button_status_e Key5Value, button_status_e Key0Value)
{

	led_brightness_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{
		(ui_show.horizontal_progress_len_brightness.position_trg > 0)?(ui_show.horizontal_progress_len_brightness.position_trg-=10):(ui_show.horizontal_progress_len_brightness.position_trg = 0);
		ws_led.Brightness = (ui_show.horizontal_progress_len_brightness.position_trg /10)*15;
		break;
	}
	
	case KEY_up:
	{
		(ui_show.horizontal_progress_len_brightness.position_trg < 100)?(ui_show.horizontal_progress_len_brightness.position_trg+=10):(ui_show.horizontal_progress_len_brightness.position_trg = 100);
		ws_led.Brightness = (ui_show.horizontal_progress_len_brightness.position_trg /10)*15;
		break ;
	}

	case KEY_enter:
	{
		
		ws_led.ws2812_setting(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color);
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();		
		Enter_Page(REMOTE_PAGE,button_none,button_none);
		break;
	}
	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(REMOTE_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}


/**
 * @brief      	LED 颜色R设置页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void remote_color_R_page_process(button_status_e Key5Value, button_status_e Key0Value)
{

	color_R_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{
		(ui_show.horizontal_progress_len.position_trg > 0)?(ui_show.horizontal_progress_len.position_trg-=10):(ui_show.horizontal_progress_len.position_trg = 0);
		ws_led.color_R = (ui_show.horizontal_progress_len.position_trg/10) * 25;
		ws_led.LED_color = ((uint32_t)ws_led.color_R << 16) | ((uint32_t)ws_led.color_G << 8) | ws_led.color_B;		// 合成32为数据
		break;
	}
	
	case KEY_up:
	{
		(ui_show.horizontal_progress_len.position_trg < 100)?(ui_show.horizontal_progress_len.position_trg+=10):(ui_show.horizontal_progress_len.position_trg = 100);
		ws_led.color_R = (ui_show.horizontal_progress_len.position_trg/10) * 25;
		ws_led.LED_color = ((uint32_t)ws_led.color_R << 16) | ((uint32_t)ws_led.color_G << 8) | ws_led.color_B;		// 合成32为数据

		if(ws_led.color_R > 225){
			ws_led.color_R = 255;
		}

		break ;
	}

	case KEY_enter:
	{
		ws_led.ws2812_setting(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color);
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();		
		Enter_Page(REMOTE_COLOR_PAGE,button_none,button_none);
		break;
	}
	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(REMOTE_COLOR_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}


/**
 * @brief      	LED 颜色G设置页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void remote_color_G_page_process(button_status_e Key5Value, button_status_e Key0Value)
{

	color_G_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{
		(ui_show.horizontal_progress_len_G.position_trg > 0)?(ui_show.horizontal_progress_len_G.position_trg-=10):(ui_show.horizontal_progress_len_G.position_trg = 0);
		ws_led.color_G = (ui_show.horizontal_progress_len_G.position_trg/10) * 25;
		ws_led.LED_color = ((uint32_t)ws_led.color_R << 16) | ((uint32_t)ws_led.color_G << 8) | ws_led.color_B;		// 合成32为数据

		break;
	}
	
	case KEY_up:
	{
		(ui_show.horizontal_progress_len_G.position_trg < 100)?(ui_show.horizontal_progress_len_G.position_trg+=10):(ui_show.horizontal_progress_len_G.position_trg = 100);
		ws_led.color_G = (ui_show.horizontal_progress_len_G.position_trg/10) * 25;
		ws_led.LED_color = ((uint32_t)ws_led.color_R << 16) | ((uint32_t)ws_led.color_G << 8) | ws_led.color_B;		// 合成32为数据

		if(ws_led.color_G > 225){
			ws_led.color_G = 255;
		}

		break ;
	}

	case KEY_enter:
	{
		ws_led.ws2812_setting(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color);								// 写入rom
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();		
		Enter_Page(REMOTE_COLOR_PAGE,button_none,button_none);
		break;
	}
	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(REMOTE_COLOR_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}


/**
 * @brief      	LED 颜色B设置页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void remote_color_B_page_process(button_status_e Key5Value, button_status_e Key0Value)
{

	color_B_ui_process();
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{
		(ui_show.horizontal_progress_len_B.position_trg > 0)?(ui_show.horizontal_progress_len_B.position_trg-=10):(ui_show.horizontal_progress_len_B.position_trg = 0);
		ws_led.color_B = (ui_show.horizontal_progress_len_B.position_trg/10) * 25;
		ws_led.LED_color = ((uint32_t)ws_led.color_R << 16) | ((uint32_t)ws_led.color_G << 8) | ws_led.color_B;		// 合成32为数据
		
		break;
	}
	
	case KEY_up:
	{
		(ui_show.horizontal_progress_len_B.position_trg < 100)?(ui_show.horizontal_progress_len_B.position_trg+=10):(ui_show.horizontal_progress_len_B.position_trg = 100);
		ws_led.color_B = (ui_show.horizontal_progress_len_B.position_trg/10) * 25;
		ws_led.LED_color = ((uint32_t)ws_led.color_R << 16) | ((uint32_t)ws_led.color_G << 8) | ws_led.color_B;		// 合成32为数据

		if(ws_led.color_B > 225){
			ws_led.color_B = 255;
		}

		break ;
	}

	case KEY_enter:
	{
		ws_led.ws2812_setting(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color);
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();		
		Enter_Page(REMOTE_COLOR_PAGE,button_none,button_none);
		break;
	}
	case KEY_home:
	{
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(MAIN_PAGE,button_none,button_none);
		break;
	}

	case KEY_esc:
	{	
		index_reset(false, 55);																		// 复位选择框与进度条
		ui_show.ui_disapper();																		// 消失函数
		Enter_Page(REMOTE_COLOR_PAGE,button_none,button_none);
		break;
	}
	default:
		break;
	}	
}


/**
 * @brief       空闲页面处理
 * @param[in]   none
 * @retval      none
 * @attention
 */
void idle_page_process(button_status_e Key5Value , button_status_e Key0Value)
{
	Serial.println("idle_page");
}