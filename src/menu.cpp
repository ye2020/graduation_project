/**
  ****************************** Y.Z.T.****************************************
  * @file       menu.c/h
  * @brief      提供键值适配等UI菜单框架数据
  * @note       框架移植自STM32工程，因项目UI子菜单仅2层，有些函数不是很必要，故稍显臃肿和混乱
  * @history    2022.7.8
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
		{CLOCK_PAGE, clock_page_process},
		{WEATHER_PAGE, weather_page_process},
		{CONFIGURATION_PAGE, configuration_page_process},
		{READ_PAGE, read_page_process},
		{GAME_PAGE, game_page_process},
		{SETTING_PAGE, setting_page_process},
		{SELECT_PAGE, select_page_process},
		{LANGUAGE_PAGE, language_page_process},
		{WORD_PAGE, word_page_process},
		{BOOK_PAGE, book_page_process}
	};


//跳转到表所对应的页面
static int JUMP_Table(menu_i32 op, button_status_e Key5Value, button_status_e Key0Value)
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
	// key5 短按2下确定
	case button_doubleclick:
	{
		Serial.println("KEY_enter");		
		return KEY_enter;
		break;
	}

	// key5 长按进入设置模式
	case button_longPressStop:
	{
		Serial.println("KEY_setting");		
		return KEY_setting;
		break;
	}

	/**************** 右按键对应键值 *******************/

	// key0 长按返回主页面
	case button_longPressStart2:
	{
		Serial.println("KEY_home");		
		return KEY_home;
		break;
	}

	// key0 短按向上
	case button_click2:
	{
		Serial.println("KEY_up");		
		return KEY_up;
		break;
	}

	// key0 短按2下返回
	case button_doubleclick2:
	{
		Serial.println("KEY_esc");		
		return KEY_esc;
		break;
	}
	default:
		break;
	}

	return KEY_none;
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

	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{

		break;
	}

	case KEY_up:
	{

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

	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{

		break;
	}

	case KEY_up:
	{

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
 * @brief       设置页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void setting_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	Serial.println("setting status");

	/*************************** 键值处理 **************************/
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{

		break;
	}

	case KEY_up:
	{

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
 * @brief       天气页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void weather_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	Serial.println("weather status");

	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

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
 * @brief       时钟页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void clock_page_process(button_status_e Key5Value, button_status_e Key0Value)
{

	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

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
 * @brief      	配置页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void configuration_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{

		break;
	}

	case KEY_up:
	{

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
 * @brief      	阅读页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void read_page_process(button_status_e Key5Value, button_status_e Key0Value)
{

	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
	case KEY_dowm:
	{

		break;
	}

	case KEY_up:
	{

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
 * @brief      	游戏页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void game_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	Serial.println("game status");

	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

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
 * @brief      	语言页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void language_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	Serial.println("language status");

	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{

		break;
	}

	case KEY_up:
	{

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
	{	//返回上一页

		break;
	}
	default:
		break;
	}	
}


/**
 * @brief       字号页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void word_page_process(button_status_e Key5Value, button_status_e Key0Value)
{
	Serial.println("word status"); 
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{
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
 * @brief       字号页面处理
 * @param[in]   KeyValue ： 键值
 * @retval      none
 * @attention
 */
void book_page_process(button_status_e Key5Value, button_status_e Key0Value)
{	
	switch (Key5Value_transition_function(Key5Value, Key0Value))
	{

	case KEY_dowm:
	{

		break;
	}

	case KEY_up:
	{

		break ;
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

