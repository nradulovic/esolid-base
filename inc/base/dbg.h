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
 * @brief       Debug module header
 * @defgroup    base_dbg Debug
 * @brief       Debugging support
 *********************************************************************//** @{ */
/**@defgroup    base_dbg_intf Interface
 * @brief       Debug support API
 * @{ *//*--------------------------------------------------------------------*/

#if !defined(DBG_H__)
#define DBG_H__

/*=========================================================  INCLUDE FILES  ==*/

#include <stdint.h>

#include "arch/compiler.h"
#include "base/dbg_cfg.h"

/*===============================================================  MACRO's  ==*/

/*------------------------------------------------------------------------*//**
 * @name        Object and error source information
 * @brief       This describes the current object file and error source
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       Declare a module information card
 * @param       modName
 *              Module name : string
 * @param       modDesc
 *              Module description : string
 * @param       modAuth
 *              Module author : string
 * @api
 */
#if (1 == CFG_DBG_ENABLE)
# define DECL_MODULE_INFO(modName, modDesc, modAuth)                            \
    static const PORT_C_ROM struct dbgModInfo_ ModInfo_ = {                     \
        modName,                                                                \
        modDesc,                                                                \
        modAuth,                                                                \
        PORT_C_FILE                                                             \
    }
#else
# define DECL_MODULE_INFO(modName, modDesc, modAuth)                            \
    PORT_C_UNUSED DECL_MODULE_INFO(modName, modDesc, modAuth)
#endif

/**@} *//*----------------------------------------------------------------*//**
 * @name        Error checking
 * @brief       These features are enabled/disabled using the option
 *              @ref CFG_DBG_ENABLE.
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       Static assert macro
 * @param       msg
 *              Message : enum esDbgMsgNum : enumerated debug message.
 * @param       expr
 *              Expression : C expression : condition expression which must be
 *              TRUE.
 * @details     This macro will evaluate the given expression at compile time.
 *              If the expression is not true the compilation process will stop
 *              with an error message about negative size of array.
 * @api
 */
#if defined(PORT_C_STATIC_ASSERT)
# define ES_DBG_STATIC_ASSERT(msg, expr)     PORT_C_STATIC_ASSERT(expr)
#else
# define ES_DBG_STATIC_ASSERT(msg, expr)                                        \
    extern char ES_DBG_STATIC_ASSERT_has_failed_##msg[(expr) ? 1 : -1]
#endif

/**@brief       Generic assert macro.
 * @param       msg
 *              Message : enum esDbgMsgNum : enumerated debug message.
 * @param       expr
 *              Expression : C expression : condition expression which must be
 *              TRUE.
 * @api
 */
#if (1 == CFG_DBG_ENABLE)
# define ES_DBG_ASSERT(msg, expr)                                               \
    do {                                                                        \
        if (!(expr)) {                                                          \
            const PORT_C_ROM struct dbgCobj_ thisObj = {                        \
                &ModInfo_,                                                      \
                PORT_C_FUNC,                                                    \
                PORT_C_LINE                                                     \
            };                                                                  \
            dbgAssert(&thisObj, #expr, msg);                                    \
        }                                                                       \
    } while (0u)
#else
# define ES_DBG_ASSERT(msg, expr)                                               \
    (void)0
#endif

/**@brief       Assert macro that will always execute (no conditional).
 * @param       msg
 *              Message : enum esDbgMsgNum : enumerated debug message.
 * @param       text
 *              Text : string : a text which will be printed when this assert
 *              macro is executed.
 * @api
 */
#if (1 == CFG_DBG_ENABLE)
# define ES_DBG_ASSERT_ALWAYS(msg, text)                                        \
    do {                                                                        \
        const PORT_C_ROM struct dbgCobj_ thisObj = {                            \
            &ModInfo_,                                                          \
            PORT_C_FUNC,                                                        \
            PORT_C_LINE                                                         \
        };                                                                      \
        dbgAssert(PORT_C_FUNC, text, msg);                                      \
    } while (0u)
#else
# define ES_DBG_ASSERT_ALWAYS(msg, text)                                        \
    (void)0
#endif

/**@} *//*----------------------------------------------------------------*//**
 * @name        Internal checking
 * @brief       These macros are enabled/disabled using the option
 *              @ref CFG_DBG_INTERNAL_CHECK.
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       Assert macro used for internal execution checking
 * @param       msg
 *              Message : enum esDbgMsgNum : enumerated debug message.
 * @param       expr
 *              Expression : C expression : condition expression which must be
 *              satisfied
 * @api
 */
#if (1 == CFG_DBG_INTERNAL_CHECK) && (1 == CFG_DBG_ENABLE)
# define ES_DBG_INTERNAL(msg, expr)                                             \
    ES_DBG_ASSERT(msg, expr)
#else
# define ES_DBG_INTERNAL(msg, expr)                                             \
    (void)0
#endif

/**@} *//*----------------------------------------------------------------*//**
 * @name        API contract validation
 * @brief       These macros are enabled/disabled using the option
 *              @ref CFG_DBG_API_VALIDATION.
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       Execute code to fulfill the contract
 * @param       expr
 *              Expression : C expression : expression to be executed only if
 *              contracts need to be validated.
 * @api
 */
#if (1 == CFG_DBG_API_VALIDATION) && (1 == CFG_DBG_ENABLE)
# define ES_DBG_API_OBLIGATION(expr)                                            \
    expr
#else
# define ES_DBG_API_OBLIGATION(expr)                                            \
    (void)0
#endif

/**@brief       Make sure the caller has fulfilled all contract preconditions
 * @param       msg
 *              Message : enum esDbgMsgNum : enumerated debug message.
 * @param       expr
 *              Expression : C expression : condition expression which must be
 *              satisfied
 * @api
 */
#if (1 == CFG_DBG_API_VALIDATION) && (1 == CFG_DBG_ENABLE)
# define ES_DBG_API_REQUIRE(msg, expr)                                          \
    ES_DBG_ASSERT(msg, expr)
#else
# define ES_DBG_API_REQUIRE(msg, expr)                                          \
    (void)0
#endif

/**@brief       Make sure the callee has fulfilled all contract postconditions
 * @param       msg
 *              Message : enum esDbgMsgNum : enumerated debug message.
 * @param       expr
 *              Expression : C expression : condition expression which must be
 *              satisfied
 * @api
 */
#if (1 == CFG_DBG_API_VALIDATION) && (1 == CFG_DBG_ENABLE)
# define ES_DBG_API_ENSURE(msg, expr)                                           \
    ES_DBG_ASSERT(msg, expr)

#else
# define ES_DBG_API_ENSURE(msg, expr)                                           \
    (void)0
#endif

/**@} *//*----------------------------------------------  C++ extern begin  --*/
#ifdef __cplusplus
extern "C" {
#endif

/*============================================================  DATA TYPES  ==*/

/*------------------------------------------------------------------------*//**
 * @name        Object and error source information
 * @{ *//*--------------------------------------------------------------------*/


/**@brief       Debug messages
 * @details     This enumeration specifies which kind of error/failure have has
 *              occurred.
 * @api
 */
enum esDbgMsgNum {
    ES_DBG_OUT_OF_RANGE,                                                        /**< @brief Value is out of valid range.                    */
    ES_DBG_OBJECT_NOT_VALID,                                                    /**< @brief Object is not valid.                            */
    ES_DBG_POINTER_NULL,                                                        /**< @brief Pointer has NULL value.                         */
    ES_DBG_USAGE_FAILURE,                                                       /**< @brief Object usage failure.                           */
    ES_DBG_NOT_ENOUGH_MEM,                                                      /**< @brief Not enough memory available.                    */
    ES_DBG_NOT_IMPLEMENTED,                                                     /**< @brief A method is not implemented                     */
    ES_DBG_UNKNOWN_ERROR                                                        /**< @brief Unknown error.                                  */
};

/**@brief       Debug C object information structure
 * @notapi
 */
struct dbgCobj_ {

/**@brief       Debug module information structure
 * @notapi
 */
    const PORT_C_ROM struct dbgModInfo_ {
        const PORT_C_ROM char * const PORT_C_ROM_VAR name;                      /**< @brief Module name                                     */
        const PORT_C_ROM char * const PORT_C_ROM_VAR desc;                      /**< @brief Module description                              */
        const PORT_C_ROM char * const PORT_C_ROM_VAR auth;                      /**< @brief Module author                                   */
        const PORT_C_ROM char * const PORT_C_ROM_VAR file;                      /**< @brief Module source file                              */
    } * const PORT_C_ROM_VAR mod;                                               /**< @brief Module information                              */
    const PORT_C_ROM char * const PORT_C_ROM_VAR fn;                            /**< @brief Function name                                   */
    uint16_t            line;                                                   /**< @brief Code line reference                             */
};

/**@brief       Debug report structure
 * @details     This detailed debug report prepared by dbgAssert() function. Use
 *              this structure to present the report to the user.
 * @api
 */
struct esDbgReport {
    const PORT_C_ROM char * modName;                                            /**< @brief Module name                                     */
    const PORT_C_ROM char * modDesc;                                            /**< @brief Module description                              */
    const PORT_C_ROM char * modAuthor;                                          /**< @brief Module author                                   */
    const PORT_C_ROM char * modFile;                                            /**< @brief Module source file                              */
    const PORT_C_ROM char * fnName;                                             /**< @brief Function name                                   */
    const PORT_C_ROM char * expr;                                               /**< @brief C expression                                    */
    const PORT_C_ROM char * msgText;                                            /**< @brief Additional text                                 */
    uint16_t            line;                                                   /**< @brief Source code line where exception occurred       */
    enum esDbgMsgNum    msgNum;                                                 /**< @brief Number associated with additional text          */
};

/**@} *//*--------------------------------------------------------------------*/

/*======================================================  GLOBAL VARIABLES  ==*/
/*===================================================  FUNCTION PROTOTYPES  ==*/

/*------------------------------------------------------------------------*//**
 * @name        Error checking
 * @details     For more details see @ref errors_intro.
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       An assertion has failed
 * @param       cObj
 *              C Object describes where the error occurred.
 * @param       expr
 *              Expression: is pointer to the string containing the expression
 *              that failed to evaluate to `TRUE`.
 * @param       msg
 *              Message: is enum esDbgMsg containing some information about the
 *              error.
 * @pre         1) `NULL != cObj`
 * @pre         2) `NULL != expr`
 * @note        1) This function is called only if @ref CFG_DBG_API_VALIDATION
 *              is active.
 * @details     Function will prepare the information which was given by the
 *              macros and pass the information to userAssert() function for
 *              presentation.
 * @notapi
 */
PORT_C_NORETURN void dbgAssert(
    const PORT_C_ROM struct dbgCobj_ * cObj,
    const PORT_C_ROM char * expr,
    enum esDbgMsgNum    msg);

/**@} *//*----------------------------------------------------------------*//**
 * @name        Debug hook functions
 * @note        1) The definition of this functions must be written by the user.
 * @{ *//*--------------------------------------------------------------------*/

/**@brief       An assertion has failed. This function should inform the user
 *              about failed assertion.
 * @param       dbgReport
 *              Debug report: is pointer to the debug report created by
 *              dbgAssert() function.
 * @pre         1) `NULL != dbgReport`
 * @note        1) This function is called only if @ref CFG_DBG_ENABLE is active.
 * @note        2) The function is called with interrupts disabled.
 * @details     Function will just print the information which was given by the
 *              macros.
 */
extern void userAssert(
    const struct esDbgReport * dbgReport);

/** @} *//*-----------------------------------------------  C++ extern end  --*/
#ifdef __cplusplus
}
#endif

/*================================*//** @cond *//*==  CONFIGURATION ERRORS  ==*/
/** @endcond *//** @} *//** @} *//*********************************************
 * END of dbg.h
 ******************************************************************************/
#endif /* DBG_H__ */
