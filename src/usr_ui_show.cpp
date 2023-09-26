
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
#include "usr_ui_show.h"

ui_show_t ui_show;


/**
 * @brief       构造函数
 * @param[in]   none
 * @retval      
 * @attention   none
 */
ui_show_t::ui_show_t()
{
    /* 菜单选项 */
    list = {
                {"test1",7},
                {"test251",9},
                {"4tet", 6},
                {"tet4", 6}
            };                         
    this->line_len = list.size(); // 选择页面数量;

   // Serial.println(list[0].str);
}

