/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_slwstk6220a
 * @{
 *
 * @file
 * @brief       Configuration of CPU peripherals for the WSTK6220 board
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include <stdint.h>
#include "cpu.h"
#include "periph_cpu.h"

#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @name    Clock configuration
 * @{
 */
#ifndef CLOCK_HF
#define CLOCK_HF            cmuSelect_HFXO
#endif
#ifndef CLOCK_CORE_DIV
#define CLOCK_CORE_DIV      1
#endif
#ifndef CLOCK_LFA
#define CLOCK_LFA           cmuSelect_LFRCO
#endif
#ifndef CLOCK_LFB
#define CLOCK_LFB           cmuSelect_LFRCO
#endif
#ifndef CLOCK_LFE
#define CLOCK_LFE           cmuSelect_LFRCO
#endif
    
#define cmuClock_CORELE cmuSelect_LFXO
#define cmuClock_HFPER cmuSelect_HFXO
    
    /** @} */

    /**
 * @name    Timer configuration
 * @{
 */
    static const timer_conf_t timer_config[] = {
        {
            {
                .dev = TIMER0,
                .cmu = cmuClock_TIMER0
            },
            {
                .dev = TIMER1,
                .cmu = cmuClock_TIMER1
            },
            .irq = TIMER1_IRQn
        }
    };

#define TIMER_0_ISR isr_timer1
#define TIMER_0_MAX_VALUE (0xffff) /* 16-bit timer */
#define TIMER_NUMOF ARRAY_SIZE(timer_config)
    /** @} */

    /**
 * @name    UART configuration
 * @{
 */
    static const uart_conf_t uart_config[] = {
        {
            USART0,          /* device */
            GPIO_PIN(PA, 6), /* RX pin */
            GPIO_PIN(PA, 5), /* TX pin */
            1,               /* AF location */
            cmuClock_PCLK,   /* bit in CMU enable register */
            USART0_RX_IRQn   /* IRQ base channel */
        },
    };

#define UART_0_ISR_RX isr_usart0_rx

#define UART_NUMOF ARRAY_SIZE(uart_config)
    /** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
/** @} */
