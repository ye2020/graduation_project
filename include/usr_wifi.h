#ifndef _USR_WIFI_H
#define _USR_WIFI_H

class usr_wifi_t{
    public:
    void get_wifi(const char* SSID,const char* Password);     //连接 wifi
    void wifi_smartconfig(void);

    private:
    int usr_wifi_status;                                      // 连接状态

    typedef enum{
        wifi_connect_fail = 0,                                // 连接失败
        wifi_connect_success,                                 // 连接成功

    }usr_wifi_status_e;
    

};


 
extern usr_wifi_t usr_Wifi;

#endif
