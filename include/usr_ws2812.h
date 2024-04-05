/**
 * *********************************** Y.Z.T. *************************************
 * 
 * @file       usr_ws2812.h
 * @brief      灯珠驱动控制
 * 
 * @author     Y.Z.T      (yezhaotin@outlook.com)
 * @date       2024-03-30
 * ============================================================================== 
 *  
 * ==============================================================================
 * @version    1.0
 * *********************************** Y.Z.T. *************************************
 */
#ifndef USR_WS2812_H
#define USR_WS2812_H

#include "Arduino.h"



// typedef struct OP_LED_STRUCT
// {
//     int op_menu ; 				//操作菜单
//     led_op_func opfun ;	        //操作方法
// }OP_LED_FUNC;

/* led模式 */
typedef enum 
{
    THEATER_CHASE_RAINBOW_LED = 0, // 闪烁彩虹灯
    FILL_LED,                   // 纯色灯
    WATER_LED = 0,              // 流水灯
    RAINBOW_LED,                // 彩虹灯
    THEATER_CHASE_LED,          // 闪烁灯
    METEOR_LED,                 // 流星灯
    METEOR_OVERTURN_LED,        // 反向流星灯
    

}WS_LED_mode_e;


class usr_ws2812_t
{
    public:
    uint8_t Brightness = 20;                // 初始亮度
    WS_LED_mode_e LED_mode = FILL_LED;      // LED模式

    uint32_t LED_color = 0xFF0000;          // LED颜色
    uint8_t color_R = 0xFF;
    uint8_t color_G = 0; 
    uint8_t color_B = 0;

    bool LED_state = false;                 // LED开关
    uint8_t wait;                           // LED间隔时间



    typedef void (usr_ws2812_t::*led_op_func)(uint8_t, uint8_t, uint8_t, uint8_t);        // led模式切换操作函数

    led_op_func g_ledmode_Struct[7];         // 回调函数集
    
    usr_ws2812_t(){
        g_ledmode_Struct[0] = &usr_ws2812_t::ws2812_theaterChase_rainbow;
        g_ledmode_Struct[1] = &usr_ws2812_t::ws2812_fill;
        g_ledmode_Struct[2] = &usr_ws2812_t::ws2812_waterled;
        g_ledmode_Struct[3] = &usr_ws2812_t::ws2812_rainbowled;
        g_ledmode_Struct[4] = &usr_ws2812_t::ws2812_theaterChase;
        g_ledmode_Struct[5] = &usr_ws2812_t::ws2812_meteor;
        g_ledmode_Struct[6] = &usr_ws2812_t::ws2812_meteor_overturn;
    }

    void ws2812_led_init(void);             // 初始化
    void ws2812_led_loop(void);             // 循环函数
    void ws2812_waterled(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);         // 流水灯
    void ws2812_rainbowled(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);       // 彩虹灯
    void ws2812_theaterChase(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);            // 闪烁流水
    void ws2812_theaterChase_rainbow(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);     // 闪烁彩虹
    void ws2812_meteor(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);             // 流星灯
    void ws2812_meteor_overturn(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);  // 反向流星灯
    void ws2812_fill(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait);             // 全亮
    void ws2812_control(uint8_t Brightness, WS_LED_mode_e LED_mode, uint32_t LED_color, uint8_t wait);              // 总控函数
    void ws2812_setting(uint8_t Brightness, WS_LED_mode_e LED_mode, uint32_t LED_color);                    // 设置函数

    void ws2812_on(void);
    void ws2812_off(void);



};


void ws2812_power_callback(void);             //测试函数

extern usr_ws2812_t ws_led; 

#endif