/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    keyboard.c
 * @brief   按键模块
 * @author  卢玮
 ******************************************************************/

#include "keyboard.h"
#include "display.h"
#include "sound.h"

static uint8_t buttom_now = 0;   ///< 此次扫描时的按键
static uint8_t buttom_last = 0;  ///< 上次扫描时的按键

static work_mode_t mode = Play;    ///< 当前的工作模式，0为自由弹奏模式，1为教学模式

void TMR1Init(void) {
    T1CONbits.TMR1CS = 0b00;     // 时钟源为Fosc/4
    T1CONbits.T1CKPS = 0b01;     // 1:2预分频
    PIE1bits.TMR1IE = 1;         // 启动timer1中断
    TMR_N_SET_ISR_FUNC(1, TMR1Func); // 设置Timer1中断函数

    return;
}

void TMR1Func(void) {
    uint8_t flag = 0;            // flag用于记录是否扫描到按键

    // 将timer1重置
    PIR1bits.TMR1IF = 0;
    TMR1H = SCANTIME_H;
    TMR1L = SCANTIME_L;

    flag += Scan0();
    flag += Scan1();
    flag += Scan2();
    flag += Scan3();
    flag += Scan4();

    // 扫描完成后flag未增加，说明本次扫描未按键
    if (!flag) {
        buttom_now = 0;
        // 只有当这次按键为第一次时，才执行功能
        if (buttom_now != buttom_last) {
            SoundFini();
            TouchButtomFiniPage();
            buttom_last = buttom_now;
        }
    }

    return;
}

void KeyboardInit(void) {
    TMR1Init();
    
    OPTION_REGbits.nWPUEN = 0;   // 使能全局弱上拉
    TRISA = 0b11111011;          // 初始时，除DAC需要使用的RA2，全部设置为输入
    ANSELA = 0b00000100;         // 初始时，除DAC需要使用的RA2，全部设置为数字
    WPUA = 0b00011011;           // 初始时，全部弱上拉取消，只保留一直弱上拉的RA0、RA1、RA3、RA4

    TMR1H = SCANTIME_H;
    TMR1L = SCANTIME_L;
    T1CONbits.TMR1ON = 1;        // 使能timer1

    return;
}

uint8_t Scan0(void) {
    if (!KEYM1) {
        if (KEYM2) {
            // 功能键1
            buttom_now = 100;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                buttom_last = buttom_now;
                // 切换模式，并更改展示页面
                mode = !mode;
                ChangeModePage(mode);
            }
        }
        return 1;
    } else if (!KEYM2) {
        if (KEYM1) {
            // 功能键2
            buttom_now = 200;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                buttom_last = buttom_now;
                // 切换音阶，并更改展示页面
                SetSoundLevel();
                uint8_t sound_level = GetSoundLevel();
                ChangeLevelPage(sound_level);
            }
        }
        return 1;
    }

    return 0;
}

uint8_t Scan1(void) {
    SCAN1_RW;
    SCAN1_WPU;

    if (!KEYC1) {
        if (KEYC2 && KEYC3 && KEYC4 && KEYC5 && KEYM1 && KEYM2) {
            // 按键4，对应音频7功能
            buttom_now = 4;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(7);
                TouchingButtomPage(7);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC2) {
        if (KEYC3 && KEYC4 && KEYC5 && KEYM1 && KEYM2) {
            // 按键10，对应音频5功能
            buttom_now = 10;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(5);
                TouchingButtomPage(5);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC3) {
        if (KEYC4 && KEYC5 && KEYM1 && KEYM2) {
            // 按键13， 对应音频3功能
            buttom_now = 13;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(3);
                TouchingButtomPage(3);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC4) {
        if (KEYC5 && KEYM1 && KEYM2) {
            // 按键15，对应音频1功能
            buttom_now = 15;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(1);
                TouchingButtomPage(1);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC5) {
        if (KEYM1 && KEYM2) {
            // 按键16，对应音频2+功能
            buttom_now = 16;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(9);
                TouchingButtomPage(9);
                buttom_last = buttom_now;
            }
        }
        return 1;
    }

    return 0;
}

uint8_t Scan2(void) {
    SCAN2_RW;
    KEYC5 = 0;
    SCAN2_WPU;

    if (!KEYC1) {
        if (KEYC2 && KEYC3 && KEYC4 && KEYM1 && KEYM2) {
            // 按键3，对应音频6功能
            buttom_now = 3;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(6);
                TouchingButtomPage(6);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC2) {
        if (KEYC3 && KEYC4 && KEYM1 && KEYM2) {
            // 按键9，对应音频4功能
            buttom_now = 9;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(4);
                TouchingButtomPage(4);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC3) {
        if (KEYC4 && KEYM1 && KEYM2) {
            // 按键12，对应音频3+功能
            buttom_now = 12;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(10);
                TouchingButtomPage(10);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC4) {
        if (KEYM1 && KEYM2) {
            // 按键14，对应音频1+功能
            buttom_now = 14;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(8);
                TouchingButtomPage(8);
                buttom_last = buttom_now;
            }
            return 1;
        }
    }

    return 0;
}

uint8_t Scan3(void) {
    SCAN3_RW;
    KEYC5 = 0;
    KEYC4 = 0;
    SCAN3_WPU;
    
    if (!KEYC1) {
        if (KEYC2 && KEYC3 && KEYM1 && KEYM2) {
            // 按键2，对应音频6+功能
            buttom_now = 2;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(13);
                TouchingButtomPage(13);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC2 && KEYM1 && KEYM2) {
        if (KEYC3) {
            // 按键8，对应音频4+功能
            buttom_now = 8;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(11);
                TouchingButtomPage(11);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC3) {
        if (KEYM1 && KEYM2) {
            // 按键11，对应音频2功能
            buttom_now = 11;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(2);
                TouchingButtomPage(2);
                buttom_last = buttom_now;
            }
        }
        return 1;
    }

    return 0;
}

uint8_t Scan4(void) {
    SCAN4_RW;
    KEYC5 = 0;
    KEYC4 = 0;
    KEYC3 = 0;
    SCAN4_WPU;
    
    if (!KEYC1) {
        if (KEYC2 && KEYM1 && KEYM2) {
            // 按键1，对应音频7+功能
            buttom_now = 1;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(14);
                TouchingButtomPage(14);
                buttom_last = buttom_now;
            }
        }
        return 1;
    } else if (!KEYC2) {
        if (KEYM1 && KEYM2) {
            // 按键7，对应音频5+功能
            buttom_now = 7;
            // 只有当这次按键为第一次时，才执行功能
            if (buttom_now != buttom_last) {
                SoundRhythm(12);
                TouchingButtomPage(12);
                buttom_last = buttom_now;
            }
        }
        return 1;
    }

    return 0;
}
