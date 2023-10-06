/**
  ****************************** Y.Z.T.****************************************
  * @file       usr_ui_show.c/h
  * @brief      用于存放ui绘制相关的数据和方法
  * @note       none
  * 
  * @author     Y.Z.T
  * @history    2023.9.26
  *
  @verbatim     v1.0
  ==============================================================================

  ==============================================================================
  @endverbatim
  ****************************** Y.Z.T. *****************************************
  */
#ifndef _USR_UI_SHOW_H
#define _USR_UI_SHOW_H

#include <Arduino.h>
#include <vector>
#include <U8g2lib.h>
#include "usr_buletooth.h"



// ACE图标 width: 50, height: 50
const unsigned char ACE[] U8X8_PROGMEM = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x0c,0x00,0x00,0x00,0x00,0x00,0xc0,0x0c,0x00,0x00,0x00,0x00,0x00,0xc0,
                                           0x1c,0x00,0x00,0x00,0x00,0x00,0xe0,0x1c,0x00,0x00,0x00,0x00,0x00,0xf0,0x3c,0x00,0x00,0x00,0x00,0x00,0xf0,0x3c,0x00,0x00,
                                           0x00,0x00,0x00,0xf8,0x7c,0x00,0x00,0x00,0x00,0x00,0xf8,0xfc,0x00,0x00,0x00,0x00,0x00,0xfc,0xfc,0x00,0x00,0x00,0x00,0x00,
                                           0xfc,0xfc,0x01,0x00,0x00,0x00,0x00,0xfe,0xfc,0x01,0x00,0x00,0x00,0x00,0xff,0xfc,0x03,0x00,0x00,0x00,0x00,0xff,0xfc,0x03,
                                           0x00,0x00,0x00,0x80,0xff,0xfc,0x07,0x00,0x00,0x00,0x80,0xff,0xfc,0x0f,0x00,0x00,0x00,0xc0,0x7f,0xf8,0x0f,0x00,0x00,0x00,
                                           0xc0,0x7f,0xf8,0x1f,0x00,0x00,0x00,0xe0,0x3f,0xf0,0x1f,0x00,0x00,0x00,0xf0,0x3f,0xe0,0x3f,0x00,0x00,0x00,0xf0,0x1f,0xe0,
                                           0x3f,0x00,0x00,0x00,0xf8,0x0f,0xc0,0x7f,0x00,0x00,0x00,0xf8,0x0f,0xc0,0xff,0x00,0x00,0x00,0xfc,0x07,0x80,0xff,0x00,0x00,
                                           0x00,0xfc,0x07,0x00,0xff,0x01,0x00,0x00,0xfe,0x03,0x03,0xff,0x01,0x00,0x00,0xff,0x03,0x07,0xfe,0x03,0x00,0x00,0xff,0x81,
                                           0x07,0xfe,0x03,0x00,0x00,0xfe,0xc0,0x0f,0xfc,0x01,0x00,0x00,0xfe,0xc0,0x0f,0xfc,0x01,0x00,0x00,0x7c,0xe0,0x1f,0xf8,0x00,
                                           0x00,0x00,0x78,0xe0,0x3f,0xf0,0x00,0x00,0x00,0x38,0xf0,0x3f,0x70,0x00,0x00,0x00,0x30,0xf0,0x38,0x60,0x00,0x00,0x00,0x10,
                                           0x70,0x38,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                                           0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x00,0x80,0xc1,0xcd,0x3f,0x00,0x00,0x00,
                                           0x80,0xe1,0x08,0x00,0x00,0x00,0x00,0x00,0x63,0x00,0x00,0x00,0x00,0x00,0x40,0x23,0xc0,0x3e,0x00,0x00,0x00,0x60,0x26,0x80,
                                           0x3e,0x00,0x00,0x00,0x60,0x67,0x00,0x00,0x00,0x00,0x00,0xb0,0xcf,0x9c,0x1f,0x00,0x00,0x00,0x30,0xcc,0xcd,0x3f,0x00,0x00,
                                           0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };


// 配网二维码
// width: 50, height: 50
const unsigned char QR_code_50_50[] U8X8_PROGMEM =  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xfc,0x13,0xe8,0x9f,0x8f,0x7f,0x00,0x04,
0x22,0x88,0x8e,0x9c,0x40,0x00,0xf4,0x42,0x7e,0xb1,0x98,0x5e,0x00,0xf4,0x42,0x7e,0xb1,0x98,0x5e,0x00,0xf4,0x12,0x92,0x4d,0x94,0x5e,0x00,0xf4,0x82,0x1b,0xf1,0x8f,0x5e,
0x00,0x04,0x02,0xf2,0xb3,0x9c,0x40,0x00,0xfc,0x53,0x6a,0xad,0x94,0x7f,0x00,0x00,0x80,0x71,0xd3,0x13,0x00,0x00,0x00,0x80,0x71,0xd3,0x13,0x00,0x00,0xb0,0x73,0x80,0x83,
0x7b,0x44,0x00,0xf8,0xec,0x67,0xc3,0xf3,0x61,0x00,0xb8,0x5f,0x6e,0x4f,0x83,0x67,0x00,0x84,0xad,0xe5,0xdf,0x77,0x43,0x00,0x84,0xad,0xe5,0xdf,0x77,0x43,0x00,0xc4,0x73,
0xe2,0xe0,0x9b,0x40,0x00,0x38,0xcc,0xe9,0x02,0x87,0x7c,0x00,0x48,0xe3,0xfb,0x9d,0x00,0x79,0x00,0xcc,0xc1,0x6f,0x6f,0x6f,0x02,0x00,0xf4,0x32,0x94,0xe3,0xfb,0x44,0x00,
0xf4,0x32,0x94,0xe3,0xfb,0x44,0x00,0xf0,0x11,0x08,0x5d,0xf4,0x7c,0x00,0x04,0x0e,0x84,0xa2,0x93,0x7e,0x00,0x8c,0x31,0x84,0x42,0x17,0x24,0x00,0xcc,0xe3,0x09,0x7c,0xfb,
0x21,0x00,0xcc,0xe3,0x09,0x7c,0xfb,0x21,0x00,0xcc,0x4c,0x72,0x53,0x83,0x58,0x00,0x08,0x6f,0x8e,0x03,0x63,0x66,0x00,0xc4,0xc1,0x01,0xf1,0x93,0x40,0x00,0x4c,0x63,0xf8,
0x91,0xfb,0x20,0x00,0x78,0x6c,0x9a,0x71,0xf0,0x7c,0x00,0x78,0x6c,0x9a,0x71,0xf0,0x7c,0x00,0xb4,0xdf,0x1f,0x3d,0x04,0x7c,0x00,0xc8,0x3c,0xec,0xa1,0xe3,0x60,0x00,0x34,
0x6e,0x78,0x81,0xf7,0x23,0x00,0x00,0x90,0x19,0x32,0x1b,0x62,0x00,0x00,0x90,0x19,0x32,0x1b,0x62,0x00,0xfc,0x23,0x1a,0xa1,0x9f,0x7a,0x00,0x04,0x32,0x16,0xce,0x13,0x62,
0x00,0xf4,0x72,0x70,0xbf,0xf7,0x27,0x00,0xf4,0x02,0x18,0xa0,0x68,0x7b,0x00,0xf4,0x32,0x10,0x2c,0x10,0x5e,0x00,0xf4,0x32,0x10,0x2c,0x10,0x5e,0x00,0x04,0x42,0x1e,0x71,
0xfb,0x20,0x00,0xfc,0x23,0x66,0xdf,0xfb,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };


//小程序二维码
// width: 50, height: 50
const unsigned char QR_wechat_50_50[] U8X8_PROGMEM = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x0c,0x04,0x00,0x00,0x00,0x00,
0x80,0x88,0x00,0x04,0x00,0x00,0x00,0x80,0xc0,0x40,0x04,0x00,0x00,0x00,0x80,0x88,0x04,0x40,0x00,0x00,0x00,0x00,0x98,0x24,0x62,0x00,0x00,0x00,0x00,0x03,0x24,0x20,0x00,
0x00,0x00,0x2e,0x92,0x00,0xd1,0x01,0x00,0x00,0x11,0x12,0x04,0x40,0x02,0x00,0x00,0x55,0xa4,0x84,0x21,0x02,0x00,0x00,0x09,0xa4,0x80,0x44,0x1b,0x00,0x00,0x02,0x81,0xd5,
0x86,0x00,0x00,0x00,0x11,0x0b,0x40,0x13,0x00,0x00,0x00,0x44,0xe2,0x0f,0x89,0x01,0x00,0x18,0x8c,0x58,0x35,0x8c,0x10,0x00,0x00,0x31,0xf5,0x6f,0x32,0x08,0x00,0x00,0x63,
0x5a,0x95,0x18,0x01,0x00,0x00,0x08,0x55,0x15,0xc1,0x80,0x00,0x40,0x30,0xad,0x4a,0x12,0xf8,0x00,0xc0,0x83,0xaa,0xa2,0x02,0x0b,0x00,0x00,0x1a,0x29,0x49,0x65,0x00,0x00,
0x12,0x40,0x52,0x52,0x0d,0x40,0x00,0x56,0x94,0x8a,0x54,0xaf,0x76,0x00,0x00,0x40,0x51,0xea,0x0b,0x00,0x00,0x00,0x10,0x8a,0x7a,0x4f,0x00,0x00,0xf0,0x51,0xb5,0xdf,0xed,
0x66,0x00,0x00,0x80,0xed,0xf6,0x07,0x00,0x00,0x00,0xd8,0xfe,0xfd,0xa7,0x00,0x00,0x80,0x82,0xbb,0xef,0x87,0x06,0x00,0x18,0x20,0x7f,0xfb,0x13,0xa0,0x00,0x00,0x0c,0xff,
0xff,0xc3,0x80,0x00,0x80,0x67,0xfe,0xff,0x09,0x02,0x00,0x80,0x30,0xfd,0xff,0x30,0x08,0x00,0x18,0x88,0xf0,0x3f,0x06,0x60,0x00,0x00,0x40,0xc2,0x0f,0x89,0x40,0x00,0x00,
0x01,0x09,0x40,0xa3,0x06,0x00,0x40,0x94,0xa1,0x54,0x52,0x08,0x00,0x60,0x8b,0x04,0x80,0xa4,0x02,0x00,0x00,0x91,0x84,0xa4,0x28,0x08,0x00,0x00,0x09,0x80,0x00,0x90,0x0a,
0x00,0x00,0x2e,0x92,0x20,0x50,0x0a,0x00,0x00,0x00,0x03,0x24,0x02,0x05,0x00,0x00,0x00,0x91,0x64,0x62,0x05,0x00,0x00,0x80,0x01,0x40,0x04,0x01,0x00,0x00,0x80,0x80,0x40,
0x00,0x00,0x00,0x00,0x40,0x00,0x44,0x00,0x00,0x00,0x00,0x00,0x00,0xc0,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };


// 红外传感器
// width: 50, height: 47
const unsigned char ir_check_50_47[] U8X8_PROGMEM = { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0x00,0x00,0x00,0x00,0xc0,0xff,0x01,0x00,0x00,0x00,0x00,0xe0,0x80,0x03,0x00,0x00,0x00,0x00,0x30,0x00,0x07,0x00,0x00,0x00,0x00,
0x18,0x00,0x06,0x00,0x00,0x00,0x00,0x18,0x00,0x0c,0x80,0x00,0x00,0x00,0x0c,0x00,0x0c,0x80,0x01,0x00,0x00,0x0c,0x00,0x18,0x80,0x03,0x00,0x00,0x0c,0x00,0x18,0x00,0x07,0x00,
0x00,0x0c,0x00,0x18,0x00,0x06,0x00,0x00,0x0c,0x00,0x18,0x00,0x0c,0x00,0x00,0x0c,0x00,0x18,0x00,0x1c,0x00,0x00,0x0c,0x00,0x0c,0x18,0x18,0x00,0x00,0x18,0x00,0x0c,0x30,0x18,
0x00,0x00,0x38,0x00,0x06,0x70,0x30,0x00,0x00,0x70,0x00,0x07,0x60,0x30,0x00,0x00,0xe0,0xc1,0x03,0xc0,0x30,0x00,0x00,0xc0,0xff,0x80,0xc1,0x60,0x00,0x00,0xe0,0xff,0x01,0xc3,
0x61,0x00,0x00,0xf8,0xc0,0x07,0x87,0x61,0x00,0x00,0x1c,0x00,0x0e,0x86,0x61,0x00,0x00,0x0e,0x00,0x1c,0x86,0x61,0x00,0x00,0x03,0x00,0x30,0x86,0x61,0x00,0x80,0x01,0x00,0x00,
0x86,0x61,0x00,0xc0,0x01,0x00,0x00,0x86,0x61,0x00,0xc0,0x00,0x00,0x00,0x86,0x61,0x00,0x60,0x00,0x00,0x00,0x83,0x61,0x00,0x60,0x00,0x00,0x80,0xc3,0x30,0x00,0x70,0x00,0x00,
0x80,0xc1,0x30,0x00,0x30,0x00,0x00,0x00,0x60,0x30,0x00,0x30,0x00,0x00,0x00,0x60,0x18,0x00,0x30,0x00,0x00,0x00,0x30,0x18,0x00,0x30,0x00,0x00,0x00,0x18,0x0c,0x00,0x00,0x00,
0x00,0x00,0x18,0x0c,0x00,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x00,0x00,0x00,0x00,0x00,0x07,0x00,0x00,0x00,0x00,0x00,0x80,0x03,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,
0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

// 红外传感器未检测
// width: 50, height: 47
const unsigned char ir_fail_50_47[] U8X8_PROGMEM =  { 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x7f,0x00,0x00,0x00,0x00,0x00,0xc0,0xff,0x01,0x00,0x00,0x00,0x00,0xe0,0x80,0x03,0x00,0x00,0x00,0x00,0x30,0x00,0x07,0x00,0x00,0x00,0x00,
0x18,0x00,0x06,0x00,0x00,0x00,0x00,0x18,0x00,0x0c,0x00,0x00,0x00,0x00,0x0c,0x00,0x0c,0x00,0x00,0x00,0x00,0x0c,0x00,0x18,0x00,0x00,0x00,0x00,0x0c,0x00,0x18,0x00,0x00,0x00,
0x00,0x0c,0x00,0x18,0x00,0x00,0x00,0x00,0x0c,0x00,0x18,0x00,0x00,0x00,0x00,0x0c,0x00,0x18,0x00,0x00,0x00,0x00,0x0c,0x00,0x0c,0x00,0x00,0x00,0x00,0x18,0x00,0x0c,0x00,0x00,
0x00,0x00,0x38,0x00,0x06,0x0c,0x40,0x00,0x00,0x70,0x00,0x07,0x18,0x60,0x00,0x00,0xe0,0xc1,0x03,0x30,0x30,0x00,0x00,0xc0,0xff,0x00,0x60,0x18,0x00,0x00,0xe0,0xff,0x01,0xc0,
0x0c,0x00,0x00,0xf8,0xc0,0x07,0x80,0x07,0x00,0x00,0x1c,0x00,0x0e,0x00,0x03,0x00,0x00,0x0e,0x00,0x1c,0x80,0x07,0x00,0x00,0x03,0x00,0x30,0xc0,0x0c,0x00,0x80,0x01,0x00,0x00,
0x60,0x18,0x00,0xc0,0x01,0x00,0x00,0x30,0x30,0x00,0xc0,0x00,0x00,0x00,0x18,0x60,0x00,0x60,0x00,0x00,0x00,0x0c,0xc0,0x00,0x60,0x00,0x00,0x00,0x06,0x80,0x00,0x70,0x00,0x00,
0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 };

// width: 13, height: 10
const unsigned char wifi_13_10[] U8X8_PROGMEM = { 0xf0,0x01,0x1c,0x07,0x07,0x1c,0xf1,0x11,0x1c,0x07,0x44,0x04,0xf0,0x01,0x10,0x01,0x40,0x00,0x40,0x00 };

// wifi断
const unsigned char dis_wifi_13_11[] U8X8_PROGMEM = { 0x00,0x08,0x00,0x0c,0xf8,0x07,0xfe,0x0f,0xbf,0x1f,0xde,0x0f,0xac,0x07,0xd0,0x03,0xe8,0x01,0xe4,0x00,0x02,0x00 };


// 
const unsigned char battery_16_9[] U8X8_PROGMEM =  { 0xfc,0x7f,0x02,0x80,0x9a,0xbb,0x9b,0xb3,0x9b,0xb3,0x9b,0xb3,0x9a,0xb3,0x02,0x80,0xfc,0x7f };

/* 位置与位置期望 */
typedef struct 
{
    int16_t cur_position;       // 当前位置
    int16_t position_trg;       // 期望位置

}position_expect_t;


/* 存放ui绘制相关的数据的方法 */
class ui_show_t{
    public:

    position_expect_t menu_x_position = {0, 0};                                      // 菜单x位置与期望    
    position_expect_t menu_y_position = {28, 28};                                    // 菜单y位置与期望
    position_expect_t frame_len = {55, 55};                                          // 选择框的宽度
    position_expect_t frame_y = {17, 17};                                            // 选择框的高度
    position_expect_t progress_position {16, 16};                                    // 进度条的位置

    uint8_t max_bar;                                                        // 进度条最底部的位置
    uint8_t y_offset = 16;                                                  // y偏移值 , 为了不在最上面的黄色部分显示
    uint8_t text_bottom_index = 2;                                          // 最底部索引, 指向当前显示最底部的表单
    uint8_t text_top_index = 0;                                             // 最顶部索引, 指向当前显示最顶部的表单


    int16_t line_len;                                                       // 选择页面的数量
    uint8_t single_line_length;                                             // 进度条单元格长度
    uint8_t total_line_length;                                              // 进度条长竖线的长度

    int16_t wifi_line_len;                                                  // wifi页面的数量
    uint8_t wifi_single_line_length;                                        // 进度条单元格长度

    int16_t remote_line_len;                                                  // wifi页面的数量
    uint8_t remote_single_line_length;                                        // 进度条单元格长度

    uint8_t screen_length = 128;                                            // 屏幕长度
    uint8_t screen_height = 64 ;                                            // 屏幕高度

    
    /* 菜单相关属性 */
    typedef struct                                                          
    {                               
        String str;                                                          // 选项名字符串
        int len;                                                             // 该选项的长度用于设置选择框的长度(一般设置为字符个数 + 2)
    }Ui_list_t;                             


    std::vector<Ui_list_t> list;                                             // 菜单项数组
    std::vector<Ui_list_t> wifi_list;                                        // wifi配置页面子菜单
    std::vector<Ui_list_t> remote_list;                                      // 遥控页面子菜单

    ui_show_t();                                                            // 构造函数

    int  ui_run(int16_t *res, int16_t *res_trg, int16_t step);              // 实现动画效果(渐进)
    void select_ui_show(int16_t speed_x, int16_t speed_y);                  // 选择框绘制函数
    void ui_init(void);                                                     // ui初始化函数
    void progress_ui_show(int16_t list_len, uint8_t single_length);         // 进度条绘制函数
    void menu_ui_show(std::vector<Ui_list_t>& list);                         // 菜单绘制函数
    bool ui_disapper(void);                                                 // 消失函数

    private:







};


extern ui_show_t ui_show;

void ui_test(button_status_e keybt0, button_status_e keybt1);
void top_ui_show(void);


#endif