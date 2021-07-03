/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    dac.h
 * @brief   TLC5615芯片的使用
 *
 * @date    2021-6-27
 * @author  卢玮
 * @note    TLC5615芯片初始化和通信的封装
 *
 * @date    2021-7-3
 * @author  董瑞华
 * @note    注释变为Doxygen风格
 ******************************************************************/

#ifndef PIANO_DAC_H_
#define PIANO_DAC_H_

#include "base.h"

/// @brief  设置DAC的CS(`LATC6`)为高电平
#define DACCS_H LATCbits.LATC6 = 1

/// @brief  设置DAC的CS(`LATC6`)为低电平
#define DACCS_L LATCbits.LATC6 = 0

/// @brief  TLC5615 DAC芯片SPI传输的初始化函数
void DACInit(void);

/// @brief  TLC5615 DAC芯片的数据传输函数
/// @param  data 需要传输的数据，为16位
void WriteDAC(uint16_t data);

#endif // PIANO_DAC_H_
