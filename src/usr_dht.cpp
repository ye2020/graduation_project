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

#if 1

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

#if 0

#define data 4   //DHT11的Data引脚(2Pin)接到NodeMcu开发板的D1引脚

usr_dht_t usr_dht;              // 实例化用户数据类


unsigned char i;  //无符号8位整型变量
float RH,T;       //单精度浮点数（32位长度）
byte RH_H,RH_L,T_H,T_L,sum,check;  //字节变量，二进制数



void usr_DHT11(void)
{
  RH_H=0,RH_L=0,T_H=0,T_L=0,sum=0,check=0;
  pinMode(data,OUTPUT);   //设置IO口为输出模式
  digitalWrite(data,1);   //设置IO口输出高电平
  delay(10);              //延时10毫秒
  digitalWrite(data,0);   //设置IO口输出低电平
  delay(25);              //延时25毫秒
  digitalWrite(data,1);   //设置IO口输出高电平
  pinMode(data,INPUT);    //设置IO口为输入模式
  delayMicroseconds(30);  //延时30微秒
  if(!digitalRead(data))  //判断IO口输入电平是否低电平
  {//https://blog.zeruns.tech
    while(!digitalRead(data));  //一直循环至输入为高电平
    while(digitalRead(data));   //一直循环至输入为低电平
    for(i=0;i<8;i++)            //循环执行8次
    {   
      while(!digitalRead(data));//一直循环至输入为高电平   
      delayMicroseconds(28);    //延时28微秒
      if(digitalRead(data)){    //判断IO口输入电平是否高电平
        bitWrite(RH_H, 7-i, 1); //在二进制变量RH_H的第7-i位（从右数起）写入1     
        while(digitalRead(data));
      }
    }
    for(i=0;i<8;i++)
    {
      while(!digitalRead(data));
      delayMicroseconds(28);
      if(digitalRead(data)){
        bitWrite(RH_L, 7-i, 1);
        while(digitalRead(data));
      }
    }
    for(i=0;i<8;i++)
    {
      while(!digitalRead(data));
      delayMicroseconds(28);
      if(digitalRead(data)){      
        bitWrite(T_H, 7-i, 1);
        while(digitalRead(data));
      }
    }
    for(i=0;i<8;i++)
    {
      while(!digitalRead(data));
      delayMicroseconds(28);
      if(digitalRead(data)){      
        bitWrite(T_L, 7-i, 1);
        while(digitalRead(data));
      }
    }
    for(i=0;i<8;i++)
    {
      while(!digitalRead(data));
      delayMicroseconds(28);
      if(digitalRead(data)){      
        bitWrite(check, 7-i, 1);
        while(digitalRead(data));
      }
    }
   }
  sum=RH_H + RH_L + T_H + T_L;
  byte sum_temp=0;
  //读取sum的末8位写入sum_temp
  for(i=0;i<8;i++){
    bitWrite(sum_temp,i,bitRead(sum,i)); 
  }
  if(check==sum_temp){  //校验数据
    RH=RH_H+float(RH_L)/10;
    T=T_H+float(T_L)/10;
  }
}

void usr_dht_t::dht_init(void)
{
    // dht.begin();                //开启dht
}



void usr_dht_t::dht_data_receive(void) {     //循环函数，运行完初始化函数后不断循环运行这个函数
  delay(1000);    //延时1000毫秒
  usr_DHT11();        //获取温湿度数据
  Serial.print("Humidity:");  //向串口打印 Humidity:
  Serial.print(RH);           //向串口打印湿度数据
  Serial.print("%");
  Serial.print("  Temperature:");
  Serial.print(T);            //向串口打印温度数据
  Serial.println("C"); 
}

#endif