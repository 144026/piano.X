/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    lcd.h
 * @brief   LCD12864显示屏的使用
 *
 * @date    2021-6-27
 * @author  卢玮
 * @note    LCD12864显示屏初始化和通信的封装
 *
 * @date    2021-6-28
 * @author  李瑞源
 * @note    更改LCD数据传输封装为命令、数据两类。
 *          封装设定显示位置和字符串显示函数
 *
 * @date    2021-6-29
 * @author  董瑞华
 * @note    更改LCD display参数为char *，防止参数
 *          类型不匹配
 *
 * @date    2021-7-3
 * @author  董瑞华
 * @note    注释变为Doxygen风格
 ******************************************************************/

#ifndef PIANO_LCD_H_
#define PIANO_LCD_H_

#include "base.h"

#define LCDCS_H     LATBbits.LATB3 = 1
#define LCDCS_L     LATBbits.LATB3 = 0
#define LCDSCLK_H   LATBbits.LATB1 = 1
#define LCDSCLK_L   LATBbits.LATB1 = 0
#define LCDRST_H    LATBbits.LATB0 = 1
#define LCDRST_L    LATBbits.LATB0 = 0
#define LCDDATA     LATBbits.LATB2

/// @brief  LCD12864屏幕的初始化函数
void LCDInit(void);

/// @brief  LCD12864屏幕的Byte级传输函数
/// @param  data 传输的数据，为8位
void SendByteLCD(uint8_t data);

/// @brief  LCD12864屏幕的指令传输函数
/// @param  cmd 传输的指令，为8位
void LCDSendCMD(uint8_t cmd);

/// @brief  LCD12864屏幕的文本传输函数
/// @param  data 传输的文本数据，为8位
void LCDSendDATA(uint8_t data);

/// @brief  LCD12864屏幕的位置设定位置设定函数
/// @param  row 游标的行位置（0-3）
/// @param  col 游标的列位置（0-7）
void LCDSetPos(uint8_t row,uint8_t col);

/// @brief  LCD12864屏幕的字符串显示函数
/// @param  str 需要显示的字符串
void LCDDisplayStr(const char *str);

#endif // PIANO_LCD_H_
