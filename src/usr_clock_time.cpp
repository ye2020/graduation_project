
#include "usr_clock_time.h"
#include <NTPClient.h>
#include <WiFiUdp.h>




WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "ntp1.aliyun.com", 8 * 3600, 60000);       //udp，服务器地址，时间偏移量，更新间隔

usr_time_t usr_timer = {(String)"00", (String)"00"};                    // 将整形转换字符串的缓冲区

// NTP初始化
void clock_init(void)
{
    timeClient.begin();
}

// 更新时间数据
void clock_updata(void)
{
    timeClient.update();
}

// 返回实时小时数
String return_time_hours(void)
{
    static int16_t time_update_flag = 0;
    
    if(time_update_flag == 0)
    {
        timeClient.update();                //更新数据
        Serial.println(timeClient.getHours());
        time_update_flag = 1;
    }
    
    //拼装时间 小时和分,不够两位数需要补0
    if(timeClient.getHours() < 10) usr_timer.time_hours = "0" + String(timeClient.getHours());
    else                           usr_timer.time_hours = String(timeClient.getHours());

    return usr_timer.time_hours;
}

// 返回实时分钟数
String return_time_minutes(void)
{
    static int16_t time_update_flag = 0;
    
    if(time_update_flag == 0)
    {
        timeClient.update();
        Serial.println(timeClient.getMinutes());
        time_update_flag = 1;
    }

    //拼装时间 小时和分,不够两位数需要补0
    if(timeClient.getMinutes() < 10) usr_timer.time_minutes = "0" + String(timeClient.getMinutes());
    else                             usr_timer.time_minutes = String(timeClient.getMinutes());

    return usr_timer.time_minutes;
}