#include <ESP8266HTTPClient.h>    //网页用
#include <ESP8266WiFi.h>
#include "usr_wifi.h"

using namespace std;

usr_wifi_t usr_Wifi;
HTTPClient http;



void usr_wifi_t::get_wifi(const char* SSID,const char* Password)     //连接 wifi
{ 
  uint8_t i = 0;  //用来判断半分钟内是否联网成功 , 否则提示
  WiFi.mode(WIFI_STA);
  WiFi.begin(SSID, Password);

  while (WiFi.status() != WL_CONNECTED) 
  {   //检测 wifi 连接状态
    delay(500);
    i++;
    Serial.print(".");

    if(i>=20)
    { 
      usr_Wifi.usr_wifi_status = usr_Wifi.wifi_connect_fail;   //表示wifi连接失败
      Serial.println("Failed to connect wifi within 5s ");    // 5s内未成功连接wifi （编码显示问题 用串口输出的话 utf-8 会乱码 ，改GBK的话 显示器乱码 + 注释乱码）
      // display_partialLine(1,"5s内未成功连接wifi");
      // display_partialLine(3,"按下key5键,进入阅读模式");
      break;
    }
  }

  if( WiFi.status()  == WL_CONNECTED ) //表示wifi连接成功
  {   
    usr_Wifi.usr_wifi_status = usr_Wifi.wifi_connect_success;
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    http.setTimeout(5000);
  }

}

void usr_wifi_t::wifi_smartconfig(void)
{
    Serial.println("WiFi smart_connecting...");
    WiFi.mode(WIFI_STA);
    WiFi.beginSmartConfig();

    if(WiFi.smartConfigDone()){
        usr_Wifi.usr_wifi_status = usr_Wifi.wifi_connect_success;           //连接成功
        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        http.setTimeout(5000);
        WiFi.stopSmartConfig();
    }

    while (1)
    {
        Serial.print(".");
        delay(500);                   // wait for a second
        if (WiFi.smartConfigDone())
        {
        Serial.println("SmartConfig Success");
        Serial.printf("SSID:%s\r\n", WiFi.SSID().c_str());
        Serial.printf("PSW:%s\r\n", WiFi.psk().c_str());
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        break;
        }
    }

    usr_Wifi.get_wifi(WiFi.SSID().c_str(),WiFi.psk().c_str());          // 利用获取到的SSID和psw 进行网络连接
}