/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_msp430fxyz
 * @ingroup     drivers_periph_uart
 * @{
 *
 * @file
 * @brief       Low-level UART driver implementation
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include "cpu.h"
#include "periph_cpu.h"
#include "periph_conf.h"
#include "periph/uart.h"

/**
 * @brief   Keep track of the interrupt context
 * @{
 */
static uart_rx_cb_t ctx_rx_cb;
static void *ctx_isr_arg;
/** @} */

static int init_base(uart_t uart, uint32_t baudrate);


int uart_init(uart_t uart, uint32_t baudrate, uart_rx_cb_t rx_cb, void *arg)
{
    if (init_base(uart, baudrate) < 0) {
        return -1;
    }

    /* save interrupt context */
    ctx_rx_cb = rx_cb;
    ctx_isr_arg = arg;

    /* reset interrupt flags and enable RX interrupt */
    UART_IF &= ~(UART_IE_RX_BIT);
    UART_IF |=  (UART_IE_TX_BIT);
    UART_IE |=  (UART_IE_RX_BIT);
    UART_IE &= ~(UART_IE_TX_BIT);

    return 0;
}

static int init_base(uart_t uart, uint32_t baudrate)
{
    if (uart != 0) {
        return -1;
    }

    /* get the default UART for now -> TODO: enable for multiple devices */
    //msp_usci_t *dev = UART_BASE;

    /* put device in reset mode while configuration is going on */
    UART_BASE->CTL1 = USCI_CTL1_SWRST;

    /* configure to UART, using SMCLK in 8N1 mode */
    UART_BASE->CTL1 |= USCI_CTL1_SSEL_ACLK;
    UART_BASE->CTL0 = 0;
    UART_BASE->STAT = 0;

    /* configure baudrate */
//    uint32_t base = ((MSP430_INITIAL_CPU_SPEED << 7)  / baudrate);
//    uint16_t br = (uint16_t)(base >> 7);
//    uint8_t brs = (((base & 0x3f) * 8) >> 7);
//    UART_BASE->BR0 = (uint8_t)br;
//    UART_BASE->BR1 = (uint8_t)(br >> 8);
//    UART_BASE->MCTL = (brs << USCI_MCTL_BRS_SHIFT);

    UART_BASE->BR0 = 3;
    UART_BASE->BR1 = 0;
    UART_BASE->MCTL = 0 | (3 << 1) | (0 << 4);


    /* pin configuration -> TODO: move to GPIO driver once implemented */
    UART_RX_PORT->SEL |= UART_RX_PIN;
    UART_TX_PORT->SEL |= UART_TX_PIN;
    UART_RX_PORT->DIR &= ~(UART_RX_PIN);
    UART_TX_PORT->DIR |= UART_TX_PIN;

    /* releasing the software reset bit starts the UART */
    UART_BASE->CTL1 &= ~(USCI_CTL1_SWRST);

    return 0;
}

void uart_write(uart_t uart, const uint8_t *data, size_t len)
{
    (void)uart;

    for (size_t i = 0; i < len; i++) {
    	while (!(UART_IF & UART_IE_TX_BIT)) {}
        //while (UART_BASE->STAT & USCI_STAT_BUSY) {}

        UART_BASE->TXBUF = data[i];
    }
}

void uart_poweron(uart_t uart)
{
    (void)uart;
    /* n/a */
}

void uart_poweroff(uart_t uart)
{
    (void)uart;
    /* n/a */
}

ISR(UART_RX_ISR, isr_uart_0_rx)
{
    __enter_isr();

    uint8_t stat = UART_BASE->STAT;
    uint8_t data = (uint8_t)UART_BASE->RXBUF;

    if (stat & (USCI_STAT_FE | USCI_STAT_OE | USCI_STAT_PE | USCI_STAT_BRK)) {
        /* some error which we do not handle, just do a pseudo read to reset the
         * status register */
        (void)data;
    }
    else {
        ctx_rx_cb(ctx_isr_arg, data);
    }

    __exit_isr();
}
