/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    sound.c
 * @brief   声音模块
 * @author  卢玮
 ******************************************************************/

#include "sound.h"

/// @brief 正弦函数表，用于构造正弦波
const uint16_t sin[20] = {513, 517, 520, 523, 524,
                    524, 523, 521, 518, 514,
                    510, 506, 503, 500, 499,
                    499, 500, 502, 505, 509};
static uint8_t index = 0;        ///< 当前所在正弦函数值索引

void TMR2Init(void) {
    T2CONbits.T2OUTPS = 0b0011;  // 1:4后分频
    T2CONbits.T2CKPS = 0b01;     // 1:4预分频
    PIE1bits.TMR2IE = 1;         // 启动timer2中断
    TMR_N_SET_ISR_FUNC(2, TMR2Func); // 设置Timer2中断函数
    
    return;
}

void TMR2Func(void) {
    // 将timer2重置
    PIR1bits.TMR2IF = 0;
    TMR2 = 0;

    WriteDAC(sin[index]);        // 到达定时，传输新的DAC数据
    switch (index) {
        case 19: {
            index = 0;           // 如果一个正弦周期已经结束，将索引重新置零
            break;
        }

        default: {
            index = index + 1;   // 正在一个正弦周期中，索引加一
            break;
        }
    }
    
    return;
}

void SoundInit(void) {
    DACInit();                   // DAC芯片初始化
    TMR2Init();                  // timer2初始化

    return;
}

void SetSoundLevel(void) {
    sound_level = !sound_level;

    return;
}

uint8_t GetSoundLevel(void) {
    return sound_level;
}

void SoundRhythm(uint8_t rhythm) {
    // 初始化timer2置0，初始化正弦函数值索引
    TMR2 = 0;
    index = 0;

    // 根据rhythm设置timer2的匹配中断值
    if (rhythm > 0 && rhythm < 15) {
        PR2 = rhythm_list[sound_level][rhythm - 1];
        T2CONbits.TMR2ON = 1;        // 启动timer2
    }

    return;
}

void SoundFini(void) {
    T2CONbits.TMR2ON = 0;        // 关闭timer2
    WriteDAC(0);                 // 给DA芯片写入0，起到输出电压为0的作用，关闭声音

    return;
}
