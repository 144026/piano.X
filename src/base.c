/*******************************************************************
 * @copyright Copyright(c) 2021 NetSec \n
 * All rights reserved.
 *
 * @file    base.c
 * @brief   该项目的最基础设置
 * @author  卢玮
 ******************************************************************/

#include "base.h"

void OSCInit(void) {
    OSCCONbits.SPLLEN = 1;
    OSCCONbits.SCS = 0b00;
    OSCCONbits.IRCF = 0b1111;
    OSCTUNE = 0b00000000;

    return;
}
