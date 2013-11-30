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
 * @brief   	Configuration of interrupt module.
 * @addtogroup  arm-none-eabi-gcc-v7-m_intr_cfg
 * @brief		Configuration of interrupt module.
 *********************************************************************//** @{ */

#if !defined(INTR_CFG_H__)
#define INTR_CFG_H__

/*=========================================================  INCLUDE FILES  ==*/

#include "family/profile.h"

/*===============================================================  DEFINES  ==*/
/*==============================================================  SETTINGS  ==*/

/**@brief       Priority of critical sections in kernel
 * @details     Specify the priority in range: <code>0</code>\f$\leq\f$
 *              <code>PORT_CFG_MAX_ISR_PRIO</code> \f$\leq\f$ <code>15</code>.
 *              The lower the number the higher the priority.
 * @note        When priority is set to @b 0 then critical code section will not
 *              use priority levels but instead it will just disable interrupts
 *              on entry and enable interrupts on exit.
 */
#if !defined(PORT_CFG_MAX_ISR_PRIO)
# define PORT_CFG_MAX_ISR_PRIO          7u
#endif

/**@brief       This field determines the split of group priority from
 *              subpriority.
 * @warning     Change this value only if you are familiar with Cortex interrupt
 *              priority system and how kernel protects its critical code
 *              sections.
 */
#if !defined(INTR_CFG_SCB_AIRCR_PRIGROUP)
# define INTR_CFG_SCB_AIRCR_PRIGROUP    0u
#endif

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//******************************************************
 * END of intr_cfg.h
 ******************************************************************************/
#endif /* INTR_CFG_H__ */
