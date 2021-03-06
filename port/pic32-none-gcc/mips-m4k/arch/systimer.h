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
 * @author  	Nenad Radulovic
 * @brief       Interface of System timer module port.
 * @addtogroup  pic32-none-gcc
 *********************************************************************//** @{ */
/**@defgroup    pic32-none-gcc-systmr System timer module
 * @brief       System timer module
 * @{ *//*--------------------------------------------------------------------*/

#ifndef ES_SYSTIMER_H_
#define ES_SYSTIMER_H_

/*=========================================================  INCLUDE FILES  ==*/

#include <stdint.h>

#include "plat/compiler.h"
#include "arch/systimer_config.h"
#include "family/profile.h"
#include "cpu.h"

/*===============================================================  MACRO's  ==*/

/*------------------------------------------------------------------------*//**
 * @name        Port constants
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       System timer one tick value
 */
#define ES_SYSTIMER_ONE_TICK                                                    \
    (CONFIG_SYSTIMER_CLOCK_FREQ / (CONFIG_SYSTIMER_EVENT_FREQ * 256))

/**@brief       Maximum number of ticks without overflowing the system timer
 */
#define ES_SYSTIMER_MAX_TICKS                                                   \
    (ES_PROFILE_MAX_SYSTIMER_VAL / ES_SYSTIMER_ONE_TICK)

/**@} *//*----------------------------------------------------------------*//**
 * @name        System timer management
 * @{ *//*--------------------------------------------------------------------*/

#define ES_MODULE_SYSTIMER_INIT()       portModuleSysTimerInit()

#define ES_MODULE_SYSTIMER_TERM()       portModuleSysTimerTerm()

#define ES_SYSTIMER_INIT(val)           portSysTimerInit_(val)

#define ES_SYSTIMER_TERM()              portSysTimerTerm_()

#define ES_SYSTIMER_GET_RVAL()          portSysTimerGetRVal_()

#define ES_SYSTIMER_GET_CVAL()          portSysTimerGetCVal_()

#define ES_SYSTIMER_RELOAD(val)         portSysTimerReload_(val)

#define ES_SYSTIMER_ENABLE()            portSysTimerEnable_()

#define ES_SYSTIMER_DISABLE()           portSysTimerDisable_()

#define ES_SYSTIMER_ISR_ENABLE()        portSysTimerIsrEnable_()

#define ES_SYSTIMER_ISR_DISABLE()       portSysTimerIsrDisable_()

#define ES_SYSTIMER_SET_HANDLER(handler)                                        \
    portSysTimerSetHandler(handler)

/**@} *//*-----------------------------------------------  C++ extern base  --*/
#ifdef __cplusplus
extern "C" {
#endif

/*============================================================  DATA TYPES  ==*/

/**@brief       System timer hardware register type.
 */
typedef uint32_t esSysTimerTick;

/*======================================================  GLOBAL VARIABLES  ==*/
/*===================================================  FUNCTION PROTOTYPES  ==*/

static PORT_C_INLINE void portSysTimerInit_(
    esSysTimerTick      tick)
{
    T1CONbits.ON = 0;
    PR1          = tick;
    TMR1         = 0;
    T1CONbits.ON = 1;
}

static PORT_C_INLINE void portSysTimerTerm_(
    void)
{
    IEC0bits.T1IE = 0;
    T1CONbits.ON = 0;
}

static PORT_C_INLINE esSysTimerTick portSysTimerGetRVal_(
    void)
{
    return (PR1);
}

static PORT_C_INLINE esSysTimerTick portSysTimerGetCVal_(
    void)
{
    return (TMR1);
}

static PORT_C_INLINE void portSysTimerReload_(
    esSysTimerTick      tick)
{
    T1CONbits.ON = 0;
    PR1          = tick;
    TMR1         = 0;
    T1CONbits.ON = 1;
}

static PORT_C_INLINE void portSysTimerEnable_(
    void)
{
    T1CONbits.ON = 1;
}


static PORT_C_INLINE void portSysTimerDisable_(
    void)
{
    T1CONbits.ON = 0;
}

static PORT_C_INLINE void portSysTimerIsrEnable_(
    void)
{
    IFS0bits.T1IF = 0;
    IEC0bits.T1IE = 1;
}

static PORT_C_INLINE void portSysTimerIsrDisable_(
    void)
{
    IEC0bits.T1IE = 0;
}

void portModuleSysTimerInit(
    void);

void portModuleSysTimerTerm(
    void);

void portSysTimerSetHandler(
    void             (* handler)(void));

/*--------------------------------------------------------  C++ extern end  --*/
#ifdef __cplusplus
}
#endif

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//** @} *//*********************************************
 * END of systimer.h
 ******************************************************************************/
#endif /* ES_SYSTIMER_H_ */
