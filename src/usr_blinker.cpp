#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT
 
#include <Blinker.h>
#include "usr_blinker.h"
#include "usr_eeprom.h"
#include "usr_clock_time.h"

 
char auth[] = "463adba036d8";
char ssid[] = "00_mi";
char pswd[] = "yezhaotin";
 
// 新建组件对象
BlinkerButton Button1("btn-abc");
BlinkerNumber Number1("num-uk5");
BlinkerRGB    Color_1("col-a75");

BlinkerText text1("tex-owp");
BlinkerSlider Slider1("ran-xml");

 
int counter = 0;

void button1_callback(const String & state);
void dataRead(const String & data);
void RGB_callback(uint8_t r_data, uint8_t g_data, uint8_t b_data, uint8_t bright_data);
void bridge_callback(int32_t data);



 

void usr_blinker_init(void)
{
    Blinker.begin(auth, ssid, pswd);
    Blinker.attachData(dataRead);                   // 绑定组件
    Button1.attach(button1_callback);
    Color_1.attach(RGB_callback);
    Slider1.attach(bridge_callback);
}


void usr_blinker_loop(void)
{
    Blinker.run();
}



// 按下按键即会执行该函数
void button1_callback(const String & state) {
    BLINKER_LOG("get button state: ", state);
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
}
 
// 如果未绑定的组件被触发，则会执行其中内容
void dataRead(const String & data)
{
    
    BLINKER_LOG("Blinker readString: ", data);
    counter++;
    Number1.print(counter);
}
 

// 取色器回调函数
void RGB_callback(uint8_t r_data, uint8_t g_data, uint8_t b_data, uint8_t bright_data)
{
    ws_led.color_R = r_data;
    ws_led.color_G = g_data;
    ws_led.color_B = b_data;

    ws_led.LED_color = ((uint32_t)ws_led.color_R << 16) | ((uint32_t)ws_led.color_G << 8) | ws_led.color_B;		// 合成32为数据
    (bright_data <= 225) ? (ws_led.Brightness = (bright_data / 25)*15) : (ws_led.Brightness = 150);     // 限制亮度最大值

    ws_led.ws2812_setting(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color);                        // 设置相关值,并写入rom

}

// 滑块回调函数
void bridge_callback(int32_t data)
{
    ws_led.ws2812_setting(ws_led.Brightness, (WS_LED_mode_e)data, ws_led.LED_color);                    // 设置相关值, 并写入rom

    switch (data)
    {
    case 0:
        text1.print("当前模式", "闪烁彩虹灯");
        break;

    case 1:
        text1.print("当前模式", "纯色灯");
        break;

    case 2:
        text1.print("当前模式", "流水灯");
        break;

    case 3:
        text1.print("当前模式", "彩虹灯");
        break;

    case 4:
        text1.print("当前模式", "闪烁灯");
        break;    

    case 5:
        text1.print("当前模式", "流星灯");
        break;

    case 6:
        text1.print("当前模式", "反向流星灯");
        break;        

    default:
        text1.print("当前模式", "未知");
        break;
    }
}