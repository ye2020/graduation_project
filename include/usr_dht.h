#ifndef _USR_DHT_H
#define _USR_DHT_H


class usr_dht_t
{
    public:
    float Hum = 0.0f;           // 湿度
    float temp = 0.0f;          // 摄氏度
    float f_temp = 0.0f;        // 华氏度

    void dht_init(void);
    void dht_data_receive(void);

};


extern usr_dht_t usr_dht;  



#endif