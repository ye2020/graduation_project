#include "usr_dht.h"
#include <DHT.h>
#include <SimpleDHT.h>



#define DHTPIN 4               // 接口
#define DHTTYPE DHT11           // DHT 11

#if 0

SimpleDHT11 dht11(DHTPIN);

usr_dht_t usr_dht;              // 实例化用户数据类


void usr_dht_t::dht_init(void)
{
    // dht.begin();                //开启dht
}



void usr_dht_t::dht_data_receive(void)
{
   byte temperature = 0;
   byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
}

#endif

#if 0

DHT dht(DHTPIN, DHTTYPE);       //初始化一个dht示例

usr_dht_t usr_dht;              // 实例化用户数据类


void usr_dht_t::dht_init(void)
{
    dht.begin();                //开启dht
}



void usr_dht_t::dht_data_receive(void)
{
    // delay(2000);                            //延时2S

     Hum = dht.readHumidity();          // 读湿度
     temp = dht.readTemperature();       // 读温度
     f_temp = dht.readTemperature(true);   // 读华氏度

    if (isnan(Hum) || isnan(temp) || isnan(f_temp)) 
    {
        Hum = 60.0f;
        temp = 30.0f;
        Serial.println("Failed to read from DHT sensor!");
        return;
    }

    Serial.print("Humidity: ");
    Serial.print(Hum);
    Serial.print(" %\t");
    Serial.print("Temperature: ");
    Serial.print(temp);
    Serial.print(" *C ");
    Serial.print(f_temp);
    Serial.print(" *F\t");


}

#endif

