
/************************** Dongguan-University of Technology -ACE**************************
 * @project   stupid_housing_system
 * @Author    Dongguan-University of Technology -ACE  叶昭廷Y.Z.T.   &&  黄崇志
 * @Date      2023-09-18

                    P                          :u7  :Ii              .
                   QBQ                     sQBBQBB  PBBBBQI.        XQBBBBBBBBBQBBBBBBBBBBBBM
                  bBBBZ                 .MQBQBBBQB  5BBBBBBBBi      uBBBBBBBBBQBBBBBBBBBQBBBP
                 bBBQQB5               XBBBRQQBBBP  sQBQBQQBBBZ     IBBBBBBBBBBBBBBBBBBBBBBBD
                 rBBgRQBY             BBQQRBBQr        rgBBBQr
               .  iBBgRQB7           BBQRgBQ:            iE.
              :BY  7BBgRQB:         sBQMgBB
             .BBB:  uBBgRBB.        BBMDQQ:                         rSU57  UQPdPbPPPPqPPbPdQs
             BBQBB:  XBQgRBB        QBggQB                          sBEQ1  QBBBBQBBBBBBBBBBBZ
            BBQgBBB   KBRDRBB       BBgDBB                          jBDQU  QBBBBBBBBBBBQBBBBg
           BBQgRBB     dQggQBB      BBggQB.                         iXJS7  uDK5XXK5KXKXXSSXg7
          gBQgRQB   BBggQDggQBQ     YBQDMBB
         PBQgRBB   BBBBBRQgMgQBg     BBQgRBB:            iZ:
        2BQgMBB.  BBBBBBBBBQRgQBK     BBBRQBBQL.      .rRBBQBr       ..                   ..
       vQBgRQB:  :uriiiiiirBQQgBB1     XQBQQQBBBBE  uBQBQBQBBBD     SBBBBBBBBBBBBBBBBBBBQBBBD
      7QBQBBBr             :BBBQBBY     .ZBQBBBBBB  qBBQBBBBB:      UBBBBQBBBBBBBBBBBBBBBBBBd
     LBBBBBBJ               7BBBBBQu       YRBBBQB  KBBBBBJ.        IBQBBBBBQBBBBBBBBBBBBBBBZ
                                                7i  .7.
*************************** Dongguan-University of Technology -ACE**************************/

#include <EEPROM.h>

#include "usr_wifi.h"
#include "main.h"
#include "usr_eeprom.h"
#include "bsp_button.h"
#include "usr_ui_show.h"
#include "usr_buletooth.h"
#include "menu.h"
#include "menu_ui.h"
#include "usr_irremote.h"
#include "usr_dht.h"
#include "usr_server.h"
#include "usr_SR505.h"


using namespace std;



void setup() {
  Serial.begin(115200);
  auto_eeprom();                                                      // 读取保存在flash中的数据
  ui_show.ui_init();                                                  // ui初始化
  Menu_Main_Init();                                                   // 菜单初始化


  usr_Wifi.wifi_init();                                               // wifi 初始化函数,自动调用上次连接成功的网络
  
  buletooth_init();                                                   // 蓝牙软串口初始化
  button_init();                                                      // 按键初始化
  usr_dht.dht_init();                                                 // 温湿度初始化
  startTCPClient();                                                   // 上传云端初始化
  sr_init();                                                          // 红外传感器初始化
  // IR_init();
  // PIN_FUNC_SELECT(PERIPHS_IO_MUX_MTDI_U, FUNC_GPIO14);
  // GPIO_OUTPUT_SET(GPIO_ID_PIN(14), 1);


}


void loop() 
{
  // IR_send();
  // IR_receive();
  // usr_dht.dht_data_receive();                        // 温湿度检查
  button_loop();                           // 按键循环函数 
  buletooth_loop();                        // 蓝牙循环函数 
  Menu_Select_main(key5_status_return(),key0_status_return());
  // doTCPClientTick();                        // 定时发送到云端
}





