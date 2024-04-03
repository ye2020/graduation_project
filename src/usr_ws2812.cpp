/**
 * *********************************** Y.Z.T. *************************************
 * 
 * @file       usr_ws2812.cpp
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

#include "usr_ws2812.h"
#include <Adafruit_NeoPixel.h>
#include "usr_eeprom.h"


const int LED_PIN = 5;          // 灯板控制引脚
const int NUMPIXELS = 18;        // 灯珠个数

Adafruit_NeoPixel WS2812(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);             // 示例化对象

usr_ws2812_t ws_led;             // 操作函数

int led_id[NUMPIXELS] = {0,1,2,3,4,5,11,10,9,8,7,6,12,13,14,15,16,17}; // 顺序遍历数组(二维数组?)

/* 灯珠id数组(二维) */
int led_id_2[3][6] = {
                        {0,1,2,3,4,5},
                        {6,7,8,9,10,11},
                        {12,13,14,15,16,17}
                     };




// OP_LED_FUNC g_ledmode_Struct[]= {
//                                     {WATER_LED, ws2812_meteor}


// };        


/**
 * @brief WS2812灯板初始化
 * 
 * 
 */
void usr_ws2812_t::ws2812_led_init(void)
{

    ws_led.Brightness = eepUserSet.eeprom_Brightness;     // 亮度(从rom中获取) 
    ws_led.LED_mode   = eepUserSet.eeprom_LED_mode;       // 模式
    ws_led.LED_color  = eepUserSet.eeprom_LED_color;      // 颜色
    ws_led.wait       = 100;

    WS2812.begin();             // 对象初始化
    ws_led.ws2812_control(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color, ws_led.wait);    // 总控函数
    
}

/**
 * @brief 三色流水灯
 * 
 * @param  wait :流水灯间隔时间
 * 
 */
void usr_ws2812_t::ws2812_waterled(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
    for(int i=0; i<NUMPIXELS; ++i)  // 设置所有灯颜色 pixels.fill(0x000000);
    {
        WS2812.setPixelColor(led_id[i], WS2812.Color(red, green, blue));
        WS2812.show();              // 刷新显示
        delay(wait);
    }

}


/**
 * @brief 彩虹灯
 * 
 * @param  waitMy Param doc
 * 
 */
void usr_ws2812_t::ws2812_rainbowled(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
     for(long firstPixelHue = 0; firstPixelHue < 5*65536; firstPixelHue += 256) 
     {
        for(int i=0; i<6; i++)  // 设置所有灯颜色 pixels.fill(0x000000);
        {
            for(int j=0; j<(NUMPIXELS/6); j++)
            {
                int pixelHue = firstPixelHue + (i * 65536L / NUMPIXELS);
                WS2812.setPixelColor(led_id_2[j][i], WS2812.gamma32(WS2812.ColorHSV(pixelHue)));
            }
            WS2812.show();              // 刷新显示     
            delay(wait);
        }
     }
}



/**
 * @brief  闪烁流水灯
 * 
 * @param  waitMy Param doc
 * 
 */
void usr_ws2812_t::ws2812_theaterChase(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
    for(int i=0; i<10; i++)  // 设置所有灯颜色 pixels.fill(0x000000);
    {
        for(int j=0; j<3; j++)
        {
            WS2812.clear();
            for(int q = j; q<NUMPIXELS; q+=3)
            {
               WS2812.setPixelColor(led_id[q],  WS2812.Color(red, green, blue));
            }

            WS2812.show();              // 刷新显示 
            delay(wait);
        }     
    }
}


/**
 * @brief 闪烁彩虹灯
 * 
 * @param  waitMy Param doc
 * 
 */
void usr_ws2812_t::ws2812_theaterChase_rainbow(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
    long firstPixelHue = 0;  // 第一个像素从红色开始(色调0)
    for(int i=0; i<30; i++)  // 设置所有灯颜色 pixels.fill(0x000000);
    {
        for(int j=0; j<3; j++)
        {
            WS2812.clear();
            for(int q = j; q<NUMPIXELS; q+=3)
            {
                int pixelHue = firstPixelHue + (i * 65536L / NUMPIXELS);
                 WS2812.setPixelColor(led_id[q], WS2812.gamma32(WS2812.ColorHSV(pixelHue)));
            }

            WS2812.show();              // 刷新显示 
            delay(wait);
            firstPixelHue+=256;
        }     
    }
}


/**
 * @brief  流星灯
 * 
 * @param  red     红色值(0~255)
 * @param  green   绿色值(0~255)
 * @param  blue    蓝色智(0~255)
 * @param  waitMy Param doc
 * 
 */
void usr_ws2812_t::ws2812_meteor(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
    const uint8_t num = 8;          // 拖尾灯数
    uint8_t max_color = red;

    if(green > max_color)
        max_color = green;
    if(blue > max_color)
        max_color = blue;

    uint8_t instance = (max_color-200)/num;

    for(uint16_t i=0; i<NUMPIXELS + num; i++) 
    {
        for(uint8_t j = 0; j < num; j ++)
        {
            if(i - j >= 0 && i - j < NUMPIXELS)
            {
                int red_after = red - (instance * j);
                int green_after = green - (instance * j);
                int blue_after = blue - (instance * j);
        
                if(j>=1)
                {
                red_after -= 200;
                green_after -= 200;
                blue_after -= 200;
                }
            WS2812.setPixelColor(led_id[i - j], WS2812.Color(red_after >= 0 ? red_after : 0, green_after >= 0 ? green_after : 0, blue_after >= 0 ? blue_after : 0));
            }
    }
    if(i - num >= 0 && i-num < WS2812.numPixels())
      WS2812.setPixelColor(led_id[i-num], 0); 

    WS2812.show();
    delay(wait);
  }

}

/**
 * @brief  反向流星灯
 * 
 * @param  red     红色值(0~255)
 * @param  green   绿色值(0~255)
 * @param  blue    蓝色智(0~255)
 * @param  waitMy Param doc
 * 
 */
void usr_ws2812_t::ws2812_meteor_overturn(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
    const uint8_t num = 8;
    uint8_t max_color = red;

    if(green > max_color)
        max_color = green;
    if(blue > max_color)
        max_color = blue;

    uint8_t instance = (max_color-200)/num;
    for(int i=WS2812.numPixels() - 1; i>=-num; i--) 
    {
        for(uint8_t j = 0; j < num; j ++)
        {
            if(i + j >= 0 && i + j < WS2812.numPixels())
            {
                int red_after = red - instance * j;
                int green_after = green - instance *  j;
                int blue_after = blue - instance *  j;

                if(j>=1)
                {
                    red_after -= 200;
                    green_after -= 200;
                    blue_after -= 200;
                }
                WS2812.setPixelColor(led_id[i + j], WS2812.Color(red_after >= 0 ? red_after : 0, green_after >= 0 ? green_after : 0, blue_after >= 0 ? blue_after : 0));
            }
        }
    if(i + num >= 0 && i+num < WS2812.numPixels())
      WS2812.setPixelColor(led_id[i+num], 0); 

    WS2812.show();
    delay(wait);
  }
}

/**
 * @brief 全亮
 * 
 * @param  redMy Param doc
 * @param  greenMy Param doc
 * @param  blueMy Param doc
 * @param  waitMy Param doc
 * 
 */
void usr_ws2812_t::ws2812_fill(uint8_t red, uint8_t green, uint8_t blue, uint8_t wait)
{
    WS2812.fill(WS2812.Color(red, green, blue));
}


/**
 * @brief  打开LED灯
 * 
 * 
 */
void usr_ws2812_t::ws2812_on(void)
{
    ws2812_control(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color, ws_led.wait);
}


/**
 * @brief 关闭LED灯
 * 
 * 
 */
void usr_ws2812_t::ws2812_off(void)
{
    WS2812.clear();             // 清空ram
    WS2812.show();
}


/**
 * @brief  总控函数, 设定整个LED的亮度,模式等
 * 
 * @param  BrightnessMy Param doc
 * @param  LED_modeMy Param doc
 * @param  LED_colorMy Param doc
 * @param  waitMy Param doc
 * 
 */
void usr_ws2812_t::ws2812_control(uint8_t Brightness, WS_LED_mode_e LED_mode, uint32_t LED_color, uint8_t wait)
{
    uint8_t r = (LED_color >> 16) & 0xFF;           // 取出r
    uint8_t g = (LED_color >> 8)  & 0xFF;
    uint8_t b = (LED_color)       & 0xFF;

    WS2812.setBrightness(Brightness);  // 设置亮度(0~255)
    (ws_led.*g_ledmode_Struct[LED_mode])(r, g, b, wait);  // 调用回调函数 

}


void usr_ws2812_t::ws2812_setting(uint8_t Brightness, WS_LED_mode_e LED_mode, uint32_t LED_color)
{
    ws_led.Brightness = Brightness;     // 亮度(从rom中获取) 
    ws_led.LED_mode   = LED_mode;       // 模式
    ws_led.LED_color  = LED_color;      // 颜色

    LED_eeprom(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color);
}

void usr_ws2812_t::ws2812_test(int wait)
{

}