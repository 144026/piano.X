/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    display.h
 * @brief   展示模块
 *
 * @date    2021-6-29
 * @author  卢玮
 * @note    展示模块初始化，开机动画和开机音频功能，默认演奏界面
 *
 * @date    2021-6-29
 * @author  卢玮
 * @note    增加模式切换、按键时、按键结束、切换音阶情况时的显示切换函数
 *
 * @date    2021-6-30
 * @author  卢玮
 * @note    将按键显示的switch case更改为表驱动
 *
 * @date    2021-7-3
 * @author  董瑞华
 * @note    注释变为Doxygen风格
 ******************************************************************/

#ifndef PIANO_DISPLAY_H_
#define PIANO_DISPLAY_H_

#include "base.h"
#include "lcd.h"

/// @brief  展示模块的初始化函数，需要初始化LCD和Sound
void DisplayInit(void);

/// @brief  开机动画和开机音频功能
void OnAnimation(void);

/// @brief  默认显示界面
void DefalutPage(void);

/// @brief  模式切换时的界面更改
/// @param  mode 切换至的工作模式，0为演奏模式，1为教学模式
void ChangeModePage(uint8_t mode);

/// @brief  音阶切换时的界面更改
/// @param  sound_level 切换至的音阶，0为Low，1为High
void ChangeLevelPage(uint8_t sound_level);

/// @brief  按键时的界面更改
/// @param  rhythm 当前按下的按键对应的音频
void TouchingButtomPage(uint8_t rhythm);

/// @brief  按键结束时的界面更改
void TouchButtomFiniPage(void);

#endif // PIANO_DISPLAY_H_
