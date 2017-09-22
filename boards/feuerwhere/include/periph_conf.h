/*
 * Copyright (C) 2017 infotec
 *
 * This file is subject to the terms and conditions of the GNU Lesser General
 * Public License v2.1. See the file LICENSE in the top level directory for more
 * details.
 */

/**
 * @ingroup     boards_feuerwhere
 * @{
 *
 * @file
 * @brief       FeuerWhere peripheral configuration
 *
 * @author      Sven Schoradt <s.schoradt@infotec-edv.de>
 */

#ifndef PERIPH_CONF_H
#define PERIPH_CONF_H

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name    Clock configuration
 * @{
 */
/** @todo   Move all clock configuration code here from the board.h */
#define CLOCK_CORECLOCK     (8000000U)

#define CLOCK_CMCLK         CLOCK_CORECLOCK     /* no divider programmed */
/** @} */

/**
 * @name    Timer configuration
 * @{
 */
#define TIMER_NUMOF         (1U)
#define TIMER_BASE          (TIMER_A0)
#define TIMER_CHAN          (5)
#define TIMER_ISR_CC0       (TIMER0_A0_VECTOR)
#define TIMER_ISR_CCX       (TIMER0_A1_VECTOR)
/** @} */

/**
 * @name    UART configuration
 * @{
 */
#define UART_NUMOF          (1U)
#define UART_0_EN           (1U)

#define UART_USE_USCI
#define UART_BASE           (USCI_A3)

#define UART_IE             (USCI_A3->IE)
#define UART_IF             (USCI_A3->IFG)
#define UART_IE_RX_BIT      (1 << 0)
#define UART_IE_TX_BIT      (1 << 1)
#define UART_RX_PORT        (PORT_10)
#define UART_RX_PIN         (1 << 5)
#define UART_TX_PORT        (PORT_10)
#define UART_TX_PIN         (1 << 4)
#define UART_RX_ISR         (USCI_A3_VECTOR)
#define UART_TX_ISR         (USCI_A3_VECTOR)
/** @} */

 /**
 * @name    SPI configuration
 * @{
 */
#define SPI_NUMOF           (0U)

/* SPI configuration */
#define SPI_USE_USCI
#define SPI_BASE            (USCI_B1)
#define SPI_IE              (SFR->IE2)
#define SPI_IF              (SFR->IFG2)
#define SPI_IE_RX_BIT       (1 << 2)
#define SPI_IE_TX_BIT       (1 << 3)
#define SPI_PIN_MISO        GPIO_PIN(P3,7)
#define SPI_PIN_MOSI        GPIO_PIN(P5,4)
#define SPI_PIN_CLK         GPIO_PIN(P5,5)
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* PERIPH_CONF_H */
