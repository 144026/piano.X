/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    sound.h
 * @brief   声音模块
 *
 * @date    2021-6-27
 * @author  卢玮
 * @note    基本的声音模块封装
 *
 * @date    2021-6-27
 * @author  卢玮
 * @note    将声音的持续时间去掉，增加SoundFini来控制声音的开关
 *
 * @date    2021-6-29
 * @author  卢玮
 * @note    增加sound_level和SetSoundLevel函数，用于切换音频范围
 *
 * @date    2021-6-29
 * @author  董瑞华
 * @note    增加sndlv_t枚举类型，使sound_level更可读
 *
 * @date    2021-6-29
 * @author  卢玮
 * @note    增加GetSoundLevel函数，用于在模块外获得音阶等级
 *
 * @date    2021-6-30
 * @author  卢玮
 * @note    将发声的switch case更改为表驱动
 *
 * @date    2021-7-3
 * @author  董瑞华
 * @note    注释变为Doxygen风格
 ******************************************************************/

#ifndef PIANO_SOUND_H_
#define PIANO_SOUND_H_

#include "base.h"
#include "dac.h"
#include "interrupt.h"

/// @brief  音频存储列表，用于存储不同的音频所需的timer2值
const uint8_t rhythm_list[3][7] = 
    {{191, 171, 152, 143, 128, 114, 101},
     { 96,  85,  76,  72,  64,  57,  51},
     { 48,  43,  38,  36,  32,  29,  26}};

/// @brief  音频版本
typedef enum {
    Low,    ///< 低音域
    High    ///< 高音域
} sndlv_t;
static sndlv_t sound_level = Low; ///< 音频切换标志位，0、1切换 

/// @brief  timer2初始化函数
void TMR2Init(void);

/// @brief  每次timer2中断后执行的函数，负责执行DAC数据传输和timer2重置
void TMR2Func(void);

/// @brief  声音模块的初始化函数，需要初始化DA芯片以及timer2
void SoundInit(void);

/// @brief  `sound_level`的切换函数，用于切换`sound_level`的0、1状态
void SetSoundLevel(void);

/// @brief  `sound_level`的获得函数，用于在其它模块可以得到`sound_level`的值
uint8_t GetSoundLevel(void);

/// @brief  声音模块的发声函数，根据输入的`rhythm`发出对应的声音
/// @param  rhythm 输入的音频标志，可输入1-14，对应两个音阶
void SoundRhythm(uint8_t rhythm);

/// @brief  声音模块的发声终止函数，关闭扬声器发声
/// @note 注意该函数只是关闭扬声器发声，下次想继续发声直接使用 `void SoundRhythm(uint8_t rhythm)` 即可，不需要重新调用 `void SoundInit(void)`
void SoundFini(void);

#endif // PIANO_SOUND_H_
