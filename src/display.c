/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    display.c
 * @brief   展示模块
 * @author  卢玮
 ******************************************************************/

#include "display.h"
#include "sound.h"

void DisplayInit(void) {
    LCDInit();
    SoundInit();

    return;
}

void OnAnimation(void) {
    LCDSetPos(0, 2);
    LCDDisplayStr("Seed");
    __delay_ms(500);
    LCDDisplayStr("2021");
    __delay_ms(500);

    LCDSetPos(1, 2);
    LCDSendDATA(14);   // 音符号
    LCDSendDATA(' ');
    LCDSendDATA(14);   // 音符号
    LCDSendDATA(' ');
    LCDSendDATA(' ');
    LCDSendDATA(14);   // 音符号
    LCDSendDATA(' ');
    LCDSendDATA(14);   // 音符号
    __delay_ms(500);

    LCDSetPos(2, 2);
    LCDDisplayStr(" Net");
    __delay_ms(500);
    LCDDisplayStr("Sec ");
    __delay_ms(500);

    LCDSetPos(3,1);
    SoundRhythm(1);
    LCDDisplayStr("L");
    __delay_ms(500);
    SoundRhythm(2);
    LCDDisplayStr("o");
    __delay_ms(500);
    SoundRhythm(3);
    LCDDisplayStr("a");
    __delay_ms(500);
    SoundRhythm(1);
    LCDDisplayStr("d");
    __delay_ms(500);
    SoundRhythm(2);
    LCDDisplayStr("i");
    __delay_ms(500);
    SoundRhythm(5);
    LCDDisplayStr("n");
    __delay_ms(500);
    SoundRhythm(5);
    LCDDisplayStr("g");
    __delay_ms(500);
    SoundFini();
    LCDDisplayStr("......");
    __delay_ms(500);

    return;
}

void DefalutPage(void) {
    LCDSendCMD(0x01);  // 清除显示
    __delay_ms(20);

    LCDSetPos(0, 0);
    LCDDisplayStr(" Mode:Play");

    LCDSetPos(0, 6);
    LCDSendDATA(21);   // 无限符
    LCDSendDATA(14);   // 音符号
    LCDSendDATA(21);   // 无限符

    LCDSetPos(1, 0);
    LCDDisplayStr(" Level:Low");

    LCDSetPos(1, 6);
    LCDSendDATA(21);   // 无限符
    LCDSendDATA(14);   // 音符号
    LCDSendDATA(21);   // 无限符

    LCDSetPos(2, 0);
    LCDDisplayStr(" Key:");

    LCDSetPos(3, 0);
    LCDDisplayStr(" Piano Seed2021 ");
}

void ChangeModePage(uint8_t mode) {
    LCDSetPos(0, 0);
    if (mode) {
        LCDDisplayStr(" Mode:Study");
    } else {
        LCDDisplayStr(" Mode:Play ");
    }

    LCDSetPos(3, 0);
    if (mode) {
        LCDDisplayStr(" Song:Two Tiger ");
    } else {
        LCDDisplayStr(" Piano Seed2021 ");
    }
}

void ChangeLevelPage(uint8_t sound_level) {
    LCDSetPos(1, 0);
    if (sound_level) {
        LCDDisplayStr(" Level:High");
    } else {
        LCDDisplayStr(" Level:Low ");
    }

    return;
}

void TouchingButtomPage(uint8_t rhythm) {
    // 按键对应的显示表
    const char * buttom_table[14] =
        {" key:1 ", " key:2 ", " key:3 ", " key:4 ", " key:5 ", " key:6 ", " key:7 ",
         " key:1+", " key:2+", " key:3+", " key:4+", " key:5+", " key:6+", " key:7+"};

    if (rhythm > 0 && rhythm < 15) {
        LCDSetPos(2, 0);
        LCDDisplayStr(buttom_table[rhythm - 1]);
    }

    return;
}

void TouchButtomFiniPage(void) {
    LCDSetPos(2, 0);
    LCDDisplayStr(" key:  ");

    return;
}
