/**
 * *********************************** Y.Z.T. *************************************
 * 
 * @file       usr_blinker.h
 * @brief      APP远程信息传输
 * 
 * @author     Y.Z.T      (yezhaotin@outlook.com)
 * @date       2024-04-07
 * ============================================================================== 
 *  
 * ==============================================================================
 * @version    1.0
 * *********************************** Y.Z.T. *************************************
 */

#define BLINKER_PRINT Serial
#define BLINKER_WIFI

extern bool blinker_enable ;         // blinker使能位

void usr_blinker_init(void);
void usr_blinker_loop(void);

