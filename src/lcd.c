/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    lcd.c
 * @brief   LCD12864显示屏的使用
 * @author  卢玮，李瑞源
 ******************************************************************/

#include "lcd.h"

void LCDSendCMD(uint8_t cmd) {
    SendByteLCD(0xf8);
    // 8位数据分开传，先是高8位，再是低8位
    SendByteLCD(cmd & 0xf0);
    SendByteLCD((cmd << 4) & 0xf0);
    __delay_us(100);
    return;
}

void LCDInit(void) {
    __delay_ms(50);
    
    // 对四个控制IO口进行配置，全部配置为输出、数字模式
    TRISBbits.TRISB3 = 0;
    TRISBbits.TRISB2 = 0;
    TRISBbits.TRISB1 = 0;
    TRISBbits.TRISB0 = 0;
    ANSELBbits.ANSB3 = 0;
    ANSELBbits.ANSB2 = 0;
    ANSELBbits.ANSB1 = 0;
    ANSELBbits.ANSB0 = 0;
    
    LCDRST_H;
    LCDRST_L;
    LCDRST_H;
    LCDSendCMD(0x30);  // 设置为8位MCU传输模式，基本指令集
    __delay_us(110);
    LCDSendCMD(0x30);
    __delay_us(50);
    LCDSendCMD(0x0c);  // 整体显示，游标不显示
    __delay_us(110);
    LCDSendCMD(0x01);  // 清除显示
    __delay_ms(20);
    LCDSendCMD(0x06);  // 指定右移显示
    
    return;
}

void SendByteLCD(uint8_t data) {
    uint8_t i;
    LCDCS_H;
    // 一位一位进行传输，从高位到低位
    for (i = 0; i < 8; ++i) {
        LCDSCLK_L;
        LCDDATA = (data & 0x80)? 1 : 0;
        LCDSCLK_H;
        data = data << 1;
    }
    LCDSCLK_L;
    LCDCS_L;
    return;
}

void LCDSendDATA(uint8_t data){
    SendByteLCD(0xfa);
    // 8位数据分开传，先是高8位，再是低8位
    SendByteLCD(data & 0xf0);
    SendByteLCD((data << 4) & 0xf0);
    __delay_us(100);
    return;
}


void LCDSetPos(uint8_t row,uint8_t col){
    uint8_t pos;
    switch (row) {
        case 0: row=0x80 ; break;
        case 1: row=0x90 ; break;
        case 2: row=0x88 ; break;
        case 3: row=0x98 ; break;
        default: break;
    }
    pos=row+col;
    LCDSendCMD(pos);
    
    return;
}

void LCDDisplayStr(const char *str){
    while (*str) {
        LCDSendDATA(*str++);    
    }
    
    return;
}
