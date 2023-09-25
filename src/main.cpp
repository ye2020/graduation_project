#include <ESP8266WiFi.h>
#include <EEPROM.h>

#include "usr_wifi.h"
#include "main.h"
#include "usr_eeprom.h"
#include "bsp_button.h"

using namespace std;





void setup() {
  Serial.begin(115200);
  auto_eeprom();
  Serial.println("wifi ssid:");
  Serial.println(eepUserSet.wifi_ssid);
  Serial.println("wifi pwd:");
  Serial.println(eepUserSet.wifi_password);

  WiFi.mode(WIFI_OFF);
  usr_Wifi.get_wifi(eepUserSet.wifi_ssid,eepUserSet.wifi_password);        // 从flash中读取

  if(WiFi.status() != WL_CONNECTED)
    usr_Wifi.wifi_smartconfig();

  button_init();                                                      // 按键初始化

}

void loop() 
{
  button_loop();                           // 按键循环函数 

}






