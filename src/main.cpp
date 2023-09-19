#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "usr_wifi.h"


using namespace std;


const char *sta_ssid1    =  "00_mi";
const char *sta_password1 =  "yezhaotin" ;





void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_OFF);
  usr_Wifi.get_wifi(sta_ssid1,sta_password1);

  if(WiFi.status() != WL_CONNECTED)
    usr_Wifi.wifi_smartconfig();
}

void loop() {
  
  delay(1000);

}




