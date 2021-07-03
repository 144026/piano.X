/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    interrupt.c
 * @brief   中断模块
 * @author  卢玮，董瑞华
 ******************************************************************/

#include "interrupt.h"

isr_func_t Tmr1IsrFunc = NULL; ///< Timer1实际上的中断事务函数
isr_func_t Tmr2IsrFunc = NULL; ///< Timer2实际上的中断事务函数

/// @brief  Timer1中断处理函数的wrapper，处理特殊情况
void static TMR1OVFvect(void);

/// @brief  Timer2中断处理函数的wrapper，处理特殊情况
void static TMR2OVFvect(void);

/// @brief  中断处理函数
void __interrupt() isr_routine(void) {
    if (PIR1bits.TMR1IF) {
        TMR1OVFvect();
    } else if (PIR1bits.TMR2IF) {
        TMR2OVFvect();
    }

    return;
}

void IntrrupterInit(void) {
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;

    return;
}

static void TMR1OVFvect(void) {
    // 确保不为NULL再调用
    if(Tmr1IsrFunc) Tmr1IsrFunc();
}

static void TMR2OVFvect(void) {
    // 确保不为NULL再调用
    if(Tmr2IsrFunc) Tmr2IsrFunc();
}
