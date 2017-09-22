/*
 * Copyright (C) 2017 infotec
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

#ifndef BOARD_H
#define BOARD_H

/**
 * @defgroup    boards_feuerwhere FeuerWhere
 * @ingroup     boards
 * @brief       Support for the IHP FeuerWhere board.
 *
<h2>Components</h2>
\li MSP430F5483A
\li CC1101

* @{
*
 * @file
 * @brief       FeuerWhere board configuration
 *
 * @author      Sven Schoradt <s.schoradt@infotec-edv.de>
 *
 */

#include <stdint.h>

#include "cpu.h"
#include "msp430_regs.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Define the CPU model for the <msp430.h>
 */
#ifndef __MSP430F5438__
#define __MSP430F5438__
#endif

/**
 * @name    Xtimer configuration
 * @{
 */
#define XTIMER_WIDTH                (16)
#define XTIMER_BACKOFF              (40)
/** @} */

/**
 * @name    CPU core configuration
 * @{
 */
/** @todo   Move this to the periph_conf.h */
#define MSP430_INITIAL_CPU_SPEED    8000000uL
#ifndef F_CPU
#define F_CPU                       MSP430_INITIAL_CPU_SPEED
#endif
#define F_RC_OSCILLATOR             32768
#define MSP430_HAS_DCOR             0
#define MSP430_HAS_EXTERNAL_CRYSTAL 1
/** @} */

/**
 * @name    LED pin definitions and handlers
 * @{
 */
#define LED_OUT_REG                 PORT_8->OD
#define LED0_MASK                   (1 << 0)
#define LED1_MASK                   (1 << 1)
#define LED2_MASK                   (1 << 2)
#define LED3_MASK                   (1 << 3)
#define LED4_MASK                   (1 << 4)
#define LED5_MASK                   (1 << 5)
#define LED6_MASK                   (1 << 6)
#define LED7_MASK                   (1 << 7)

#define LED0_ON                     (LED_OUT_REG &=~LED0_MASK)
#define LED0_OFF                    (LED_OUT_REG |= LED0_MASK)
#define LED0_TOGGLE                 (LED_OUT_REG ^= LED0_MASK)

#define LED1_ON                     (LED_OUT_REG &=~LED1_MASK)
#define LED1_OFF                    (LED_OUT_REG |= LED1_MASK)
#define LED1_TOGGLE                 (LED_OUT_REG ^= LED1_MASK)

#define LED2_ON                     (LED_OUT_REG &=~LED2_MASK)
#define LED2_OFF                    (LED_OUT_REG |= LED2_MASK)
#define LED2_TOGGLE                 (LED_OUT_REG ^= LED2_MASK)

#define LED3_ON                     (LED_OUT_REG &=~LED3_MASK)
#define LED3_OFF                    (LED_OUT_REG |= LED3_MASK)
#define LED3_TOGGLE                 (LED_OUT_REG ^= LED3_MASK)

#define LED4_ON                     (LED_OUT_REG &=~LED4_MASK)
#define LED4_OFF                    (LED_OUT_REG |= LED4_MASK)
#define LED4_TOGGLE                 (LED_OUT_REG ^= LED4_MASK)

#define LED5_ON                     (LED_OUT_REG &=~LED5_MASK)
#define LED5_OFF                    (LED_OUT_REG |= LED5_MASK)
#define LED5_TOGGLE                 (LED_OUT_REG ^= LED5_MASK)

#define LED6_ON                     (LED_OUT_REG &=~LED6_MASK)
#define LED6_OFF                    (LED_OUT_REG |= LED6_MASK)
#define LED6_TOGGLE                 (LED_OUT_REG ^= LED6_MASK)

#define LED7_ON                     (LED_OUT_REG &=~LED7_MASK)
#define LED7_OFF                    (LED_OUT_REG |= LED7_MASK)
#define LED7_TOGGLE                 (LED_OUT_REG ^= LED7_MASK)
/** @} */


/**
 * @name    UART Configuration
 * @{
 */
#define UART_STDIO_BAUDRATE         (9600U)
/** @} */

#ifdef __cplusplus
}
#endif

/** @} */
#endif /* BOARD_H */
