/**
  ****************************** Y.Z.T.****************************************
  * @file       usr_wifi.c/h
  * @brief      用于存放wifi连接和扫码配网的相关函数和类定义
  * @note       none
  * 
  * @author     Y.Z.T
  * @history    2023.9.18
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */

#ifndef _USR_WIFI_H
#define _USR_WIFI_H

class usr_wifi_t{
    public:
    void get_wifi(const char* SSID,const char* Password);     //连接 wifi
    void wifi_smartconfig(void);
    void wifi_init(void);

    private:
    int usr_wifi_status;                                      // 连接状态

    typedef enum{
        wifi_connect_fail = 0,                                // 连接失败
        wifi_connect_success,                                 // 连接成功

    }usr_wifi_status_e;
    

};


 
extern usr_wifi_t usr_Wifi;

#endif
