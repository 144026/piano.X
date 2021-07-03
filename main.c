/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    main.c
 * @author  卢玮
 * @date    2021年6月8日, 下午5:15
 ******************************************************************/

//#include "base.h"
#include "display.h"
//#include "interrupt.h"
#include "keyboard.h"
#include "sound.h"

void main(void) {
    OSCInit();
    IntrrupterInit();
    DisplayInit();
    KeyboardInit();

    OnAnimation();

    DefalutPage();

    uint8_t i, j, level;

    SetSoundLevel();
    level = GetSoundLevel();
    ChangeLevelPage(level);

    while (1) {
        __delay_ms(1000);
        ChangeModePage(1);
        __delay_ms(1000);
        ChangeModePage(0);
        for (j = 0; j < 4; ++j) {
            for (i = 1; i < 15; ++i) {
                SoundRhythm(i);
                TouchingButtomPage(i);
                __delay_ms(1000);
                SoundFini();
                TouchButtomFiniPage();
                __delay_ms(1000);
            }
            SetSoundLevel();
            level = GetSoundLevel();
            ChangeLevelPage(level);
        }
    }
    
    return;
}
