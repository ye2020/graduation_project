#include "usr_dht.h"
#include <DHT.h>



#define DHTPIN D4               // 接口
#define DHTTYPE DHT11           // DHT 11


DHT dht(DHTPIN, DHTTYPE);       //初始化一个dht示例


void dht_init(void)
{
    dht.begin();                //开启dht
}



void dht_data_receive(void)
{
    delay(2000);                            //延时2S

     float h = dht.readHumidity();          // 读湿度
     float t = dht.readTemperature();       // 读温度
     float f = dht.readTemperature(true);   // 读华氏度

    if (isnan(h) || isnan(t) || isnan(f)) 
    {
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(h);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(t);
    Serial.print(" *C ");
    Serial.print(f);
    Serial.print(" *F\t");


}