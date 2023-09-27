#include "usr_buletooth.h"

String comdata = "";

int8_t buletooth_read(void)
{
    while(Serial.available() > 0)               // 串口接收的数据大于0
    {
        comdata += char(Serial.read());
        Serial.println("Serial read");
        Serial.println(comdata);
    }

    if(comdata == "1") {
        comdata = "";
        return 1;
    } else if (comdata == "2") {
        comdata = "";
        return 2;
    } else {
        comdata = "";
        return -1;
    }
}