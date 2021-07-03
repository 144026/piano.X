/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    dac.c
 * @brief   TLC5615芯片的使用
 * @author  卢玮
 ******************************************************************/

#include "dac.h"

void DACInit(void) {
    // 设置FVR至1.024V
    FVRCON = 0b10000100;
    while(!FVRCONbits.FVRRDY);
    
    // 设置DAC输出1.02V电压作为DAC芯片的参考电压
    DACCON0 = 0b10101000;
    DACCON1 = 0b11111111;
    
    SSPCON1bits.SSPEN = 1;          // 使能SPI
    // 配置时钟上升沿时发送
    SSPCON1bits.CKP = 0;
    SSPSTATbits.CKE = 1;
    SSPCON1bits.SSPM = 0b0000;      // 主模式，时钟 = Fosc/4
    SSPSTATbits.SMP = 1;            // 在数据输出时间的中间采样输入数据
    // SPI端口配置
    TRISCbits.TRISC5 = 0;           // SDO TRIS置0
    TRISCbits.TRISC4 = 1;           // SDI TRIS置1
    TRISCbits.TRISC3 = 0;           // SCK主动模式，TRIS置0
    // DAC芯片片选初始化
    TRISCbits.TRISC6 = 0;
    DACCS_H;

    return;
}

void WriteDAC(uint16_t data) {
    data = data << 2;
    DACCS_L;
    SSPBUF = (data & 0xff00) >> 8;  // 传送数据时，先传高8位，再传低8位
    while (!PIR1bits.SSP1IF);       // 等待传输完成
    PIR1bits.SSP1IF = 0;            // 标志位置0
    SSPBUF = data & 0x00ff;         // 传送低8位
    while (!PIR1bits.SSP1IF);
    PIR1bits.SSP1IF = 0;
    DACCS_H;
    
    return;
}
