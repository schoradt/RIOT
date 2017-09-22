/*
 * board.c - Board initialization for the IHP FeuerWhere
 * Copyright (C) 2017 infotec
 *
 * Author : Sven Schoradt <s.schoradt@infotec-edv.de>
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     boards_feuerwhere
 * @{
 *
 * @file
 * @brief       Board specific implementations for the Zolertia Z1
 *
 * @author      Sven Schoradt <s.schoradt@infotec-edv.de>
 *
 * @}
 */


#include "cpu.h"
#include "board.h"
#include "uart_stdio.h"

/* "public" specific initialization function for the Zolertia Z1 hardware */

void _init_led(void)
{
#ifdef PORT_8
	PORT_8->DIR = 0xff;
	PORT_8->OD = 0xff;
#endif
}

void board_init(void)
{
	/* init CPU core */
    msp430_cpu_init();

    _init_led();

    /* disable watchdog timer */
    WDTCTL     =  WDTPW + WDTHOLD;

    /* initialize STDIO over UART */
    uart_stdio_init();

    /* enable interrupts */
    __bis_SR_register(GIE);
}
