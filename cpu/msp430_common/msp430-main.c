/*
 * Copyright (c) 2005, Swedish Institute of Computer Science
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 * Modified by Kaspar Schleiser
 */

/**
 * @ingroup     cpu
 * @{
 *
 * @file
 * @brief       MSP430 CPU initialization
 *
 * @author      Kaspar Schleiser <kaspar@schleiser.de>
 * @author      Oliver Hahm <oliver.hahm@inria.fr>
 *
 * @}
 */

#include "cpu.h"
#include "irq.h"
#include "periph/init.h"

/*---------------------------------------------------------------------------*/
static void
init_ports(void)
{
    /* Turn everything off, device drivers enable what is needed. */

    /* All configured for digital I/O */
#ifdef PORT_1
	PORT_1->SEL = 0;

	PORT_1->DIR = 0;
	PORT_1->OD = 0;

	((msp_port_isr_e_t *)PORT_1)->IE = 0;
#endif

#ifdef PORT_2
	PORT_2->SEL = 0;

	PORT_2->DIR = 0;
	PORT_2->OD = 0;

	((msp_port_isr_e_t *)PORT_2)->IE = 0;
#endif

#ifdef PORT_3
	PORT_3->SEL = 0;

	PORT_3->DIR = 0;
	PORT_3->OD = 0;
#endif

#ifdef PORT_4
	PORT_4->SEL = 0;

	PORT_4->DIR = 0;
	PORT_4->OD = 0;
#endif

#ifdef PORT_5
	PORT_5->SEL = 0;

	PORT_5->DIR = 0;
	PORT_5->OD = 0;
#endif

#ifdef PORT_6
	PORT_6->SEL = 0;

	PORT_6->DIR = 0;
	PORT_6->OD = 0;
#endif

#ifdef PORT_7
	PORT_7->SEL = 0;

	PORT_7->DIR = 0;
	PORT_7->OD = 0;
#endif

#ifdef PORT_8
	PORT_8->SEL = 0;

	PORT_8->DIR = 0;
	PORT_8->OD = 0;
#endif

#ifdef PORT_9
	PORT_9->SEL = 0;

	PORT_9->DIR = 0;
	PORT_9->OD = 0;
#endif

#ifdef PORT_10
	PORT_10->SEL = 0;

	PORT_10->DIR = 0;
	PORT_10->OD = 0;
#endif
}

/*---------------------------------------------------------------------------*/
/* msp430-ld may align _end incorrectly. Workaround in cpu_init. */
extern int _end;        /* Not in sys/unistd.h */
char *cur_break = (char *) &_end;

void msp430_cpu_init(void)
{
    irq_disable();
    init_ports();
    irq_enable();

    periph_init();

    if ((uintptr_t)cur_break & 1) { /* Workaround for msp430-ld bug!*/
        cur_break++;
    }
}
/*---------------------------------------------------------------------------*/
#define asmv(arg) __asm__ __volatile__(arg)

#define STACK_EXTRA 32

extern char __stack;     /* provided by linker script */
char *__heap_end = NULL; /* top of heap */

/*
 * Allocate memory from the heap. Check that we don't collide with the
 * stack right now (some other routine might later). A watchdog might
 * be used to check if cur_break and the stack pointer meet during
 * runtime.
 */
void *sbrk(int incr)
{
    char *__heap_top = __heap_end;

    if (!__heap_top) {
        /* set __heap_top to stack pointer if we are not in thread mode */
        asmv("mov r1, %0" : "=r"(__heap_top));
        __heap_top -= STACK_EXTRA;
    }

    if (incr > (__heap_top - cur_break)) {
        return (void *) - 1;    /* ENOMEM */
    }

    void *old_break = cur_break;
    cur_break += incr;
    /*
     * If the stack was never here then [old_break .. cur_break] should
     * be filled with zeros.
    */
    return old_break;
}
/*---------------------------------------------------------------------------*/
/*
 * Mask all interrupts that can be masked.
 */
int
splhigh_(void)
{
    /* Clear the GIE (General Interrupt Enable) flag. */
    int sr;
    asmv("mov r2, %0" : "=r"(sr));
    asmv("bic %0, r2" : : "i"(GIE));
    asmv("nop");
    return sr & GIE;        /* Ignore other sr bits. */
}
/*---------------------------------------------------------------------------*/
/*
 * Restore previous interrupt mask.
 */
void
splx_(int sr)
{
    sr &= GIE;
    /* If GIE was set, restore it. */
    asmv("bis %0, r2" : : "r"(sr));
    asmv("nop");
}
/*---------------------------------------------------------------------------*/

size_t strnlen(const char *s, size_t maxlen)
{
    size_t len;

    for (len = 0; len < maxlen; len++, s++) {
        if (!*s)
            break;
    }
    return (len);
}

extern void board_init(void);
