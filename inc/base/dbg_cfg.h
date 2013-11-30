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
 * @brief   	Debug support configuration header
 * @addtogroup  base_dbg
 *********************************************************************//** @{ */
/**@defgroup    base_dbg_cfg Configuration
 * @brief       Debug support Configuration
 * @{ *//*--------------------------------------------------------------------*/

#if !defined(DBG_CFG_H_)
#define DBG_CFG_H_

/*=========================================================  INCLUDE FILES  ==*/
/*===============================================================  DEFINES  ==*/
/*==============================================================  SETTINGS  ==*/

/**@brief       Enable/disable Debug module
 * @details     Possible values:
 *              - 0 - All debug options are disabled
 *              - 1 - Debug options can be enabled individually
 */
#if !defined(CFG_DBG_ENABLE)
# define CFG_DBG_ENABLE                 1
#endif

/**@brief       Enable/disable API arguments validation
 * @details     Possible values:
 *              - 0 - API validation is disabled
 *              - 1 - API validation is enabled
 *
 * @note        This option is enabled only if @ref CFG_DBG_ENABLE is enabled,
 *              too.
 */
#if !defined(CFG_DBG_API_VALIDATION)
# define CFG_DBG_API_VALIDATION         1
#endif

/**@brief       Enable/disable internal checks
 * @details     Possible values:
 *              - 0 - API validation is disabled
 *              - 1 - API validation is enabled
 *
 * @note        This option is enabled only if @ref CFG_DBG_ENABLE is enabled,
 *              too.
 */
#if !defined(CFG_DBG_INTERNAL_CHECK)
# define CFG_DBG_INTERNAL_CHECK         1
#endif

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/

#if ((1 != CFG_DBG_ENABLE) && (0 != CFG_DBG_ENABLE))
# error "eSolid RT Kernel: Configuration option CFG_DBG_ENABLE is out of range."
#endif

#if ((1 != CFG_DBG_API_VALIDATION) && (0 != CFG_DBG_API_VALIDATION))
# error "eSolid RT Kernel: Configuration option CFG_DBG_API_VALIDATION is out of range."
#endif

#if ((1 != CFG_DBG_INTERNAL_CHECK) && (0 != CFG_DBG_INTERNAL_CHECK))
# error "eSolid RT Kernel: Configuration option CFG_DBG_INTERNAL_CHECK is out of range."
#endif

/** @endcond *//** @} *//** @} *//*********************************************
 * END of dbg_cfg.h
 ******************************************************************************/
#endif /* DBG_CFG_H_ */
