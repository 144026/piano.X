/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    interrupt.h
 * @brief   中断相关函数
 *
 * @date    2021-6-29
 * @author  drh
 * @note    interrupt utils
 *
 * @date    2021-7-3
 * @author  董瑞华
 * @note    注释变为Doxygen风格
 ******************************************************************/

#ifndef PIANO_INTERRUPT_H_
#define PIANO_INTERRUPT_H_

#include "base.h"

/// @brief 中断事务函数类型
typedef void (*isr_func_t)(void);

/// @brief  设置TimerN的中断事务函数
/// @param n        要设置的timer
/// @param isr_func 要设置的函数
#define TMR_N_SET_ISR_FUNC(n, isr_func) do {                        \
    extern isr_func_t Tmr ## n ## IsrFunc;                          \
    Tmr ## n ## IsrFunc = isr_func;                                 \
} while(0)

/// @brief  中断初始化函数，使能全局中断、外设中断
void IntrrupterInit(void);

#endif
