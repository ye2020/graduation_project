/**
  ****************************** Y.Z.T.****************************************
  * @file       usr_ui_show.c/h
  * @brief      用于存放ui绘制相关的数据和方法
  * @note       none
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
#ifndef _USR_UI_SHOW_H
#define _USR_UI_SHOW_H

#include <Arduino.h>
#include <vector>


/* 位置与位置期望 */
typedef struct 
{
    int16_t cur_position;       // 当前位置
    int16_t position_trg;       // 期望位置

}position_expect_t;


/* 存放ui绘制相关的数据的方法 */
class ui_show_t{
    public:
    ui_show_t(void);



    private:
    position_expect_t menu_x_position;                                      // 菜单x位置与期望    
    position_expect_t menu_y_position;                                      // 菜单y位置与期望
    position_expect_t frame_len;                                            // 选择框的宽度
    position_expect_t frame_y;                                              // 选择框的高度
    position_expect_t progress_position;                                    // 进度条的位置


    uint8_t screen_length = 128;                                            // 屏幕长度
    uint8_t screen_height = 64 ;                                            // 屏幕高度

    int16_t line_len;                                                       // 选择页面的数量
    uint8_t single_line_length = (screen_height - 1) / line_len;            // 进度条单元格长度
    uint8_t total_line_length  = single_line_length * line_len + 1;         // 进度条长竖线的长度

    /* 菜单相关属性 */
    typedef struct                                                          
    {                               
        String str;                                                          // 字符串
        int len;                                                             // 用于设置选择框的长度
    }Ui_list_t;                             

    std::vector<Ui_list_t> list;                                             // 菜单项数组

};


extern ui_show_t ui_show;

#endif