
/**
  ****************************** Y.Z.T.****************************************
  * @file       usr_ui_show.c/h
  * @brief      用于存放ui绘制相关的数据和方法
  * @note       添加了用于支持中文显示的库u8g2_wqy (不知道好不好用)
  * 
  * @author     Y.Z.T
  * @history    2023.9.26
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
#include "usr_ui_show.h"
#include <Wire.h>
#include "usr_wifi.h"
#include "usr_clock_time.h"
#include "bsp_adc.h"


// U8G2_SSD1306_128X32_UNIVISION_F_SW_I2C u8g2(U8G2_R0, /* clock=*/14, /* data=*/2, /* reset=*/ U8X8_PIN_NONE);     // 0.91寸OLED驱动
// U8G2_SSD1306_128X32_UNIVISION_1_SW_I2C u8g2(U8G2_R0, /* clock=*/14, /* data=*/2, /* reset=*/ U8X8_PIN_NONE);   //这是比较常用的0.9寸的OLED显示器的驱动
// U8G2_SSD1306_128X64_NONAME_1_SW_I2C u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 2, /* reset=*/ U8X8_PIN_NONE);
U8G2_SSD1306_128X64_NONAME_F_SW_I2C u8g2(U8G2_R0, /* clock=*/ 14, /* data=*/ 2, /* reset=*/ U8X8_PIN_NONE);   // 0.96寸OLED驱动

ui_show_t ui_show;


/**
 * @brief       构造函数
 * @param[in]   none
 * @retval      
 * @attention   none
 * 
 */
ui_show_t::ui_show_t()
{
    //u8g2.setFont(u8g2_font_wqy12_t_chinese1);

    /* 菜单选项 */
    list = {
                {"网络配置", 11},
                {"蓝牙设置", 11},
                {"微信小程序", 13},
                {"LED设置", 10},
                {"红外检测", 11},
                {"关于设备", 11}
            };

    wifi_list = {
                  {"当前网络", 11},
                  {"断开网络", 11},
                  {"扫码配网", 11}
    };

    remote_list = {
                    {"开/关", 8},
                    {"设置颜色", 11},
                    {"设置模式", 11},
                    {"设置亮度", 11}
    };
            

    line_len                  = list.size();                                      // 选择页面的数量              
    single_line_length        = (screen_height - 1 - 16) / line_len;              // 进度条单元格长度
    wifi_line_len             = wifi_list.size();                                 // wifi页面数量
    wifi_single_line_length   = (screen_height - 1 - 16) / wifi_line_len;         // wifi页面单元格长度
    remote_line_len             = remote_list.size();                                 // wifi页面数量
    remote_single_line_length   = (screen_height - 1 - 16) / remote_line_len;         // wifi页面单元格长度

    total_line_length  = single_line_length * line_len + 1;                // 进度条长竖线的长度

    max_bar = single_line_length*ui_show.line_len + ui_show.y_offset;       // 进度条最底部位置

   Serial.println(list[0].str);
}


/**
 * @brief       ui初始化函数
 * @param[in]   none
 * @retval      none
 * @attention   none
 */
void ui_show_t::ui_init(void)
{
    u8g2.begin();
    u8g2.enableUTF8Print();
    u8g2.setFont(u8g2_font_wqy12_t_gb2312a);           // 设置字体

    u8g2.clearBuffer();
    u8g2.drawXBMP(40,16,50,50,ACE);
    u8g2.drawStr(30,10,"initializing...");
    u8g2.sendBuffer();    
    // u8g2.setFont(u8g2_font_ncenB08_tr);
}


/**
 * @brief       渐进函数,用于实现动画效果
 * @param[in]   *res    : 当前值
 *              *res_trg: 目标值
 *              step    : 步进长度,即移动速度
 * @retval      移动到位返回1,否则返回0
 * @attention   none
 */
int ui_show_t::ui_run(int16_t *res, int16_t *res_trg, int16_t step)
{
  if (*res < *res_trg) 
  {
    *res += step;
    if (*res > *res_trg) *res = *res_trg;         // 加完溢出
  } 

  else if (*res > *res_trg) 
  {
    *res -= step;
    if (*res < *res_trg) *res = *res_trg;         // 减完溢出
  } 

  else 
  {
    return 0;
  }
  
  return 1;
}


/**
 * @brief       选择框绘制函数
 * @param[in]   *speed_x: 选择框x轴移动速度(像素)
 *              *speed_y: 选择框y轴移动速度(像素)
 * @retval      none
 * @attention   none
 */
void ui_show_t::select_ui_show(int16_t speed_x, int16_t speed_y)
{
  u8g2.setDrawColor(2);                             // 异或,颜色反转
  // 绘制选择框 , 左上x; 左上y; 框的宽度; 框的高度; 圆角的半径
  u8g2.drawRBox(ui_show.menu_x_position.cur_position, ui_show.frame_y.cur_position, ui_show.frame_len.cur_position, 13, 1);
  u8g2.setDrawColor(1);                             // 异或,颜色恢复


  // Serial.println("frame_y_cur:");
	// Serial.println(ui_show.frame_y.cur_position);	
  // Serial.println("frame_y_trg:");
	// Serial.println(ui_show.frame_y.position_trg);	
  ui_run(&ui_show.frame_y.cur_position, &ui_show.frame_y.position_trg, speed_y);                // y轴移动(2)
  ui_run(&ui_show.frame_len.cur_position, &ui_show.frame_len.position_trg, speed_x);           // x轴移动
}
 

/**
 * @brief       进度条框绘制函数
 * @param[in]   
 * @retval      none
 * @attention   none
 */
void ui_show_t::progress_ui_show(int16_t list_len, uint8_t single_length, int16_t speed)
{
  u8g2.drawVLine(126, ui_show.y_offset + 1, total_line_length);            // 长竖线
  u8g2.drawPixel(125, ui_show.y_offset + 1);                              // 进度条最上面的小横线
  u8g2.drawPixel(127, ui_show.y_offset + 1);      

  for(uint8_t i=0; i < list_len; ++i)
  {    
    u8g2.drawPixel(125,single_length*(i+1) + ui_show.y_offset);     // 分段小横线
    u8g2.drawPixel(127,single_length*(i+1) + ui_show.y_offset);
  }


  u8g2.drawVLine(125, ui_show.progress_position.cur_position, single_length - 1);    // 进度条小框（左上角坐标x,左上角坐标y, 高度）
  u8g2.drawVLine(127, ui_show.progress_position.cur_position, single_length - 1);

  ui_run(&ui_show.progress_position.cur_position,&ui_show.progress_position.position_trg, speed);                       // 进度条移动
}



/**
 * @brief       菜单绘制函数
 * @param[in]   
 * @retval      none
 * @attention   none
 */
void ui_show_t::menu_ui_show(std::vector<Ui_list_t>& list, int16_t speed_x, int16_t speed_y)
{

    for (int i = 0; i < 3; i++ )
    {
      u8g2.drawUTF8(ui_show.menu_x_position.cur_position + 4, ui_show.menu_y_position.cur_position + i*15, list[ui_show.text_top_index + i].str.c_str());
    }

    ui_show.select_ui_show(speed_x, speed_y);                                            // 选择框UI绘制

}



/**
 * @brief       消失函数
 * @param[in]   
 * @retval      none
 * @attention   none
 */
bool ui_show_t::ui_disapper(void)
{
    int len = 8 * u8g2.getBufferTileHeight() * u8g2.getBufferTileWidth();
    uint8_t *p = u8g2.getBufferPtr();
    int8_t dis_temp = 0;

    for(int j = 0; j < 4; j++)
    {
      for (int i = 0; i < len; i++)
      {
        p[i] = p[i] & (rand()%0xff) >> dis_temp;
      }

      dis_temp += 2;
      u8g2.sendBuffer();
      // delay(1);
    }

    if(dis_temp >= 8)
    {
      dis_temp = 0;
      u8g2.clearBuffer();  
      u8g2.sendBuffer();
      return 0;
    }

    return 1;

}


/**
 * @brief 电量表头信息
 * 
 * 
 */
void top_battery_ui(void)
{
  uint8_t vol_percen = bat_vcc_percentage();  //电池电量百分比

  if( false == return_recharge_state())        // 放电状态
  {
      if(vol_percen > 75){
        u8g2.drawXBMP(108,2,20,11,battery_100_20_11);
    } else if(vol_percen <= 75 && vol_percen > 50){
        u8g2.drawXBMP(108,2,20,11,battery_75_20_11);
    } else if(vol_percen <= 50 && vol_percen > 25){
        u8g2.drawXBMP(108,2,20,11,battery_50_20_11);
    } else if(vol_percen <= 25 && vol_percen > 0){
        u8g2.drawXBMP(108,2,20,11,battery_25_20_11);
    } else if(vol_percen <= 0){
        u8g2.drawXBMP(108,2,20,11,battery_00_20_11);
    }
  }      
   else                                     // 充电状态
  {
      u8g2.drawXBMP(108,2,20,11,battery_in_black2_20_11);
  }

  u8g2.drawUTF8(100, 10, "%");
	u8g2.setCursor(88, 10);
  u8g2.print(vol_percen);

}

/**
 * @brief       绘制表头常驻UI
 * @param[in]   
 * @retval      none
 * @attention   none
 */
void top_ui_show(void)
{
 
  //  u8g2.drawXBMP(108,2,20,11,battery_in_black2_20_11);
  top_battery_ui();                 // 绘制表头电池信息

  if(WiFi.status() == WL_CONNECTED) {
     u8g2.drawXBMP(70,2,13,10,wifi_13_10);
  } else if( WiFi.status() != WL_CONNECTED) {
    u8g2.drawXBMP(70,2,13,11,dis_wifi_13_11);
  }
   
	u8g2.drawStr(10, 10, return_time_hours().c_str());
  u8g2.drawStr(26, 10, ":");
  u8g2.drawStr(33, 10, return_time_minutes().c_str());
  
}


void ui_test(button_status_e keybt0, button_status_e keybt1)
{
    u8g2.clearBuffer();  
    u8g2.drawStr(20,30,"keybt0: ");
    u8g2.setCursor(90, 30);
    u8g2.print(keybt0);
    u8g2.drawStr(20,42,"keybt1: ");
    u8g2.setCursor(90, 42);
    u8g2.print(keybt1);
    u8g2.sendBuffer();
}


