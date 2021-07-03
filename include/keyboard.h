/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    keyboard.h
 * @brief   按键模块
 *
 * @date    2021-6-28
 * @author  卢玮
 * @note    按键模块的基本框架封装。需要注意的是，目前的所有按键情况都做了多
 *          按键的判断处理。当出现同时多个按键按下时，不会进行任何处理动作
 *
 * @date    2021-6-29
 * @author  卢玮
 * @note    将mode更改为enum类型，更加易读；
 *          加入演奏模式下的全部逻辑（待测试）
 *
 * @date    2021-7-3
 * @author  董瑞华
 * @note    注释变为Doxygen风格
 ******************************************************************/

#ifndef PIANO_KEYBOARD_H_
#define PIANO_KEYBOARD_H_

#include "base.h"
#include "interrupt.h"

/// @name KEY
/// 按键标号：15 11 13 9 10 3 4 14 16 12  8  7  2  1 \n
/// 对应音频： 1  2  3 4  5 6 7 1+ 2+ 3+ 4+ 5+ 6+ 7+
/// @{
#define KEYC1      PORTAbits.RA3
#define KEYC2      PORTAbits.RA4
#define KEYC3      PORTAbits.RA5
#define KEYC4      PORTAbits.RA6
#define KEYC5      PORTAbits.RA7
#define KEYM1      PORTAbits.RA1
#define KEYM2      PORTAbits.RA0
/// @}

/// @name SCANTIME
/// 设置扫描的间隔时间，16位定时器，分高8位和低8位保存。目前定时为10ms一次扫描
/// @{
#define SCANTIME_H 0b01100011
#define SCANTIME_L 0b11000000
/// @}

/// @name SCAN
/// SCAN1：全部弱上拉：4、10、13、15、16 \n
/// SCAN2：KEYC5输出0，其余弱上拉：3、9、12、14 \n
/// SCAN3：KEYC4、KEYC5输出0，其余弱上拉：2、8、11 \n
/// SCAN4：KEYC3、KEYC4、KEYC5输出0，其余弱上拉：1、7
/// @{
#define SCAN1_RW   TRISA = 0b11111011
#define SCAN1_WPU  WPUA = 0b11111011
#define SCAN2_RW   TRISA = 0b01111011 
#define SCAN2_WPU  WPUA = 0b01111011
#define SCAN3_RW   TRISA = 0b00111011 
#define SCAN3_WPU  WPUA = 0b00111011
#define SCAN4_RW   TRISA = 0b00011011 
#define SCAN4_WPU  WPUA = 0b00011011
/// @}

/// @brief  电子琴工作模式
typedef enum {
    Play,   ///< 自由弹奏模式，值为0
    Study   ///< 教学模式，值为1
} work_mode_t;

/// @brief  timer1初始化函数
void TMR1Init(void);

/// @brief  每次timer1中断后执行的函数，负责执行按键的全扫描及后续功能
void TMR1Func(void);

/// @brief  按键模块的初始化函数，需要初始化timer1和各引脚配置
void KeyboardInit(void);

/// @brief  按键全扫描的第一部分，负责判断两个功能键的按键情况
/// @return 指示按键是否按下的flag
/// @retval 1 有按键
/// @retval 0 没有按键
uint8_t Scan0(void);

/// @brief  按键全扫描的第二部分，负责判断按键4、10、13、15、16的按键情况
/// @return 指示按键是否按下的flag
/// @retval 1 有按键
/// @retval 0 没有按键
uint8_t Scan1(void);

/// @brief  按键全扫描的第三部分，负责判断按键3、9、12、14的按键情况
/// @return 指示按键是否按下的flag
/// @retval 1 有按键
/// @retval 0 没有按键
uint8_t Scan2(void);

/// @brief  按键全扫描的第四部分，负责判断按键2、8、11的按键情况
/// @return 指示按键是否按下的flag
/// @retval 1 有按键
/// @retval 0 没有按键
uint8_t Scan3(void);

/// @brief  按键全扫描的第五部分，负责判断按键1、7的按键情况
/// @return 指示按键是否按下的flag
/// @retval 1 有按键
/// @retval 0 没有按键
uint8_t Scan4(void);

#endif
