/*
 * This file is part of eSolid.
 *
 * Copyright (C) 2010 - 2013 Nenad Radulovic
 *
 * eSolid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * eSolid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with eSolid.  If not, see <http://www.gnu.org/licenses/>.
 *
 * web site:    http://github.com/nradulovic
 * e-mail  :    nenad.b.radulovic@gmail.com
 *//***********************************************************************//**
 * @file
 * @author      Nenad Radulovic
 * @brief       Implementation of PIC32 System Timer port.
 * @addtogroup  pic32-none-gcc-systimer
 *********************************************************************//** @{ */
/**@defgroup    pic32-none-gcc-systimer_impl System Timer module Implementation
 * @brief       System Timer module Implementation
 * @{ *//*--------------------------------------------------------------------*/

/*=========================================================  INCLUDE FILES  ==*/

#include <xc.h>
#include <stddef.h>

#include "arch/systimer.h"
#include "arch/intr.h"
#include "base/bitop.h"
#include "base/debug.h"

/*=========================================================  LOCAL MACRO's  ==*/
/*======================================================  LOCAL DATA TYPES  ==*/
/*=============================================  LOCAL FUNCTION PROTOTYPES  ==*/
/*=======================================================  LOCAL VARIABLES  ==*/

static const ES_MODULE_INFO_CREATE("systimer", "System Timer (port)", "Nenad Radulovic");

static void (* GlobalSysTimerHandler[4])(void);

/*======================================================  GLOBAL VARIABLES  ==*/
/*============================================  LOCAL FUNCTION DEFINITIONS  ==*/
/*===================================  GLOBAL PRIVATE FUNCTION DEFINITIONS  ==*/
/*====================================  GLOBAL PUBLIC FUNCTION DEFINITIONS  ==*/

void portModuleSysTimerInit(
    void)
{
    T1CON = 0;
    T1CONbits.TCKPS = 3;
    IPC1bits.T1IP = CONFIG_INTR_MAX_ISR_PRIO;
}

void portModuleSysTimerTerm(
    void)
{
    ES_SYSTIMER_ISR_DISABLE();
    ES_SYSTIMER_DISABLE();
}

void portSysTimerSetHandler(
    void             (* handler)(void),
    uint_fast8_t        level) {

    ES_REQUIRE(ES_API_RANGE, level < ES_ARRAY_DIMENSION(GlobalSysTimerHandler));

    GlobalSysTimerHandler[level] = handler;
}

void __ISR(_TIMER_1_VECTOR) sysTimerHandler(
    void)
{
    unsigned int count;
    
    IFS0bits.T1IF = 0;

    for (count = 0; count < ES_ARRAY_DIMENSION(GlobalSysTimerHandler); count++) {
        if (GlobalSysTimerHandler[count] != NULL) {
            GlobalSysTimerHandler[count]();
        }
    }
}

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//** @} *//*********************************************
 * END of cpu.c
 ******************************************************************************/

