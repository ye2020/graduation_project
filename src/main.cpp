#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>    //网页用


using namespace std;



HTTPClient http;
unsigned char wifi_flag = 0 ; //wifi连接标志位  1为成功，0为失败

const char *sta_ssid1    =  "00_mi";
const char *sta_password1 =  "yezhaotin" ;

void get_wifi(const char* SSID,const char* Password);     //连接 wifi



void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  get_wifi(sta_ssid1,sta_password1);

}

void loop() {
  Serial.println("test");
  delay(1000);

}


void get_wifi(const char* SSID,const char* Password)     //连接 wifi
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
      wifi_flag = 0;   //表示wifi连接失败
      Serial.println("Failed to connect wifi within 5s ");    // 5s内未成功连接wifi （编码显示问题 用串口输出的话 utf-8 会乱码 ，改GBK的话 显示器乱码 + 注释乱码）
      // display_partialLine(1,"5s内未成功连接wifi");
      // display_partialLine(3,"按下key5键,进入阅读模式");
      break;
    }
  }

  if( WiFi.status()  == WL_CONNECTED ) //表示wifi连接成功
  {   
    wifi_flag = 1;
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    http.setTimeout(5000);
  }

}
