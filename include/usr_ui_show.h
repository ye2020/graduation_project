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

    position_expect_t menu_x_position = {0, 0};                                      // 菜单x位置与期望    
    position_expect_t menu_y_position = {27, 27};                                      // 菜单y位置与期望
    position_expect_t frame_len;                                            // 选择框的宽度
    position_expect_t frame_y;                                              // 选择框的高度
    position_expect_t progress_position;                                    // 进度条的位置

    uint8_t max_bar;                                                        // 进度条最底部的位置

    ui_show_t();                                                            // 构造函数

    int  ui_run(int16_t *res, int16_t *res_trg, int16_t step);              // 实现动画效果(渐进)
    void select_ui_show(int16_t speed_x, int16_t speed_y);                  // 选择框绘制函数
    void ui_init(void);                                                     // ui初始化函数
    void progress_ui_show(void);                                            // 进度条绘制函数
    void menu_ui_show(void);                                                // 菜单绘制函数
    bool ui_disapper(void);                                                 // 消失函数

    private:

    uint8_t screen_length = 128;                                            // 屏幕长度
    uint8_t screen_height = 64 ;                                            // 屏幕高度

    int16_t line_len;                                                       // 选择页面的数量
    uint8_t single_line_length;                                             // 进度条单元格长度
    uint8_t total_line_length;                                              // 进度条长竖线的长度

    /* 菜单相关属性 */
    typedef struct                                                          
    {                               
        String str;                                                          // 选项名字符串
        int len;                                                             // 该选项的长度用于设置选择框的长度(一般设置为字符个数 + 2)
    }Ui_list_t;                             

    std::vector<Ui_list_t> list;                                             // 菜单项数组 


};


extern ui_show_t ui_show;

#endif