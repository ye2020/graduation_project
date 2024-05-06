#define BLINKER_WIFI
#define BLINKER_MIOT_LIGHT
 
#include <Blinker.h>
#include "usr_blinker.h"
#include "usr_eeprom.h"
#include "usr_clock_time.h"
#include "bsp_adc.h"
#include "usr_buletooth.h"

 
char auth[] = "463adba036d8";
char ssid[] = "00_mi";
char pswd[] = "yezhaotin";
 
static long elec_updata_tick = 0;          // 定时上传电量数据
#define upDataTime 15*1000                  // 上传速率5s (1s<=upDataTime<=60s）
bool blinker_enable = 0;

// 新建组件对象
BlinkerButton Button1("btn-u30");           // 开关
BlinkerButton Button2("btn-04q");           // 蓝牙开关
BlinkerNumber Number1("num-uk5");           // 当前电量
BlinkerNumber Number2("num-dq6");           // R
BlinkerNumber Number3("num-tow");           // G
BlinkerNumber Number4("num-lrv");           // B

BlinkerRGB    Color_1("col-a75");           // 取色器

BlinkerText text1("tex-owp");               // 灯光状态显示
BlinkerSlider Slider1("ran-xml");           // 滑块

 
int counter = 0;

void button1_callback(const String & state);
void button2_callback(const String & state);
void RGB_callback(uint8_t r_data, uint8_t g_data, uint8_t b_data, uint8_t bright_data);
void bridge_callback(int32_t data);
void dataStorage(void);
void miotPowerState(const String & state);
void miotColor(int32_t color);
void miotBright(const String & bright);
void miotQuery(int32_t queryCode);
void miotMode(uint8_t mode);







 

void usr_blinker_init(void)
{
    Blinker.begin(auth, eepUserSet.wifi_ssid, eepUserSet.wifi_password);
    // Blinker.attachData(dataRead);                   // 绑定组件
    Button1.attach(button1_callback);
    Button2.attach(button2_callback);                   // 蓝牙开关
    Color_1.attach(RGB_callback);
    Slider1.attach(bridge_callback);
    Blinker.attachDataStorage(dataStorage);
    BlinkerMIOT.attachPowerState(miotPowerState);       // 电源回调
    BlinkerMIOT.attachColor(miotColor);                 // 颜色回调
    BlinkerMIOT.attachBrightness(miotBright);           // 亮度回调
    BlinkerMIOT.attachQuery(miotQuery);                 // 查询回调
    BlinkerMIOT.attachMode(miotMode);                   // 模式回调

}


void usr_blinker_loop(void)
{
    Blinker.run();
    if(millis() - elec_updata_tick >= upDataTime)
    {
        elec_updata_tick = millis();
        Number1.print(bat_vcc_percentage());        // 电量信息上传
        Number2.print(ws_led.color_R);
        Number3.print(ws_led.color_G);
        Number4.print(ws_led.color_B);
    }

}



// 按下按键即会执行该函数
void button1_callback(const String & state) {
    
    if(state == "tap")
    {
         ws2812_power_callback();                    // 回调函数
    } 
    else if(state == "on")
    {
        ws_led.LED_state = true;
        LED_state_eeprom(ws_led.LED_state);
    }
    else if(state == "off")
    {
        ws_led.LED_state = false;
        LED_state_eeprom(ws_led.LED_state);
    }
}
 
void button2_callback(const String & state) 
{
    static bool i = 0;
    if( i == 0){
        buletooth_on();
        i = 1;
    } else {
        buletooth_off();;
        i = 0;
    }
}

 
void dataStorage()
{
    Blinker.dataStorage("data1", bat_vcc_percentage());
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


// 米家电源回调函数
void miotPowerState(const String & state)
{
    BLINKER_LOG("need set power state: ", state);

    if (state == BLINKER_CMD_ON) {
        ws_led.LED_state = true;
        LED_state_eeprom(ws_led.LED_state);


        BlinkerMIOT.powerState("on");
        BlinkerMIOT.print();
    }
    else if (state == BLINKER_CMD_OFF) {
        ws_led.LED_state = false;
        LED_state_eeprom(ws_led.LED_state);

        BlinkerMIOT.powerState("off");
        BlinkerMIOT.print();
    }
}


// 小爱颜色设置回调函数
void miotColor(int32_t color)
{
    // BLINKER_LOG("need set color: ", color);

    ws_led.color_R = color >> 16 & 0xFF;
    ws_led.color_G = color >>  8 & 0xFF;
    ws_led.color_B = color       & 0xFF;
    ws_led.ws2812_setting(ws_led.Brightness, ws_led.LED_mode, color);                        // 设置相关值,并写入rom

    // BLINKER_LOG("colorR: ", ws_led.color_R, ", colorG: ", ws_led.color_G, ", colorB: ", ws_led.color_B);
    

    BlinkerMIOT.color(color);
    BlinkerMIOT.print();
}

// 小爱亮度设置回调函数
void miotBright(const String & bright)
{
    // BLINKER_LOG("need set brightness: ", bright);

    ws_led.Brightness = (bright.toInt()/10)*15;                        // 转成整形

    // BLINKER_LOG("now set brightness: ", colorW);
    ws_led.ws2812_setting(ws_led.Brightness, ws_led.LED_mode, ws_led.LED_color);                        // 设置相关值,并写入rom

    BlinkerMIOT.brightness(ws_led.Brightness);
    BlinkerMIOT.print();
}


// 状态查询函数
void miotQuery(int32_t queryCode)
{
    // BLINKER_LOG("MIOT Query codes: ", queryCode);

    switch (queryCode)
    {
        case BLINKER_CMD_QUERY_ALL_NUMBER :
            BLINKER_LOG("MIOT Query All");
            BlinkerMIOT.powerState(ws_led.LED_state ? "on" : "off");
            BlinkerMIOT.color(ws_led.LED_color);
            BlinkerMIOT.mode(ws_led.LED_mode);
            BlinkerMIOT.brightness(ws_led.Brightness/15*10);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_POWERSTATE_NUMBER :
            BLINKER_LOG("MIOT Query Power State");
            BlinkerMIOT.powerState(ws_led.LED_state ? "on" : "off");
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_COLOR_NUMBER :
            BLINKER_LOG("MIOT Query Color");
            BlinkerMIOT.color(ws_led.LED_color);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_MODE_NUMBER :
            BLINKER_LOG("MIOT Query Mode");
            BlinkerMIOT.mode(ws_led.LED_mode);
            BlinkerMIOT.print();
            break;
        case BLINKER_CMD_QUERY_BRIGHTNESS_NUMBER :
            BLINKER_LOG("MIOT Query Brightness");
            BlinkerMIOT.brightness(ws_led.Brightness/15*10);
            BlinkerMIOT.print();
            break;
        default :
            BlinkerMIOT.powerState(ws_led.LED_state ? "on" : "off");
            BlinkerMIOT.color(ws_led.LED_color);
            BlinkerMIOT.mode(ws_led.LED_mode);
            BlinkerMIOT.brightness(ws_led.Brightness/15*10);
            BlinkerMIOT.print();
            break;
    }
}



void miotMode(uint8_t mode)
{
    // BLINKER_LOG("need set mode: ", mode);
    ws_led.ws2812_setting(ws_led.Brightness, (WS_LED_mode_e)mode, ws_led.LED_color);                    // 设置相关值, 并写入rom

    if (mode == BLINKER_CMD_MIOT_DAY) {
        text1.print("当前模式", "闪烁彩虹灯");
    }
    else if (mode == BLINKER_CMD_MIOT_NIGHT) {
        text1.print("当前模式", "纯色灯");
    }
    else if (mode == BLINKER_CMD_MIOT_COLOR) {
        text1.print("当前模式", "流水灯");
    }
    else if (mode == BLINKER_CMD_MIOT_WARMTH) {
        text1.print("当前模式", "彩虹灯");
    }
    else if (mode == BLINKER_CMD_MIOT_TV) {
        text1.print("当前模式", "闪烁灯");
    }
    else if (mode == BLINKER_CMD_MIOT_READING) {
        text1.print("当前模式", "流星灯");
    }
    else if (mode == BLINKER_CMD_MIOT_COMPUTER) {
       text1.print("当前模式", "反向流星灯");
    }


    BlinkerMIOT.mode(ws_led.LED_mode);
    BlinkerMIOT.print();
}