/*
 * Copyright (C) 2015 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_msp430fxyz
 * @ingroup     drivers_periph_gpio
 * @{
 *
 * @file
 * @brief       Low-level GPIO driver implementation
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include "cpu.h"
#include "bitarithm.h"
#include "periph/gpio.h"

/**
 * @brief   Number of possible interrupt lines: 2 ports * 8 pins
 */
#define ISR_NUMOF           (16U)

/**
 * @brief   Number of pins on each port
 */
#define PINS_PER_PORT       (8U)

/**
 * @brief   Interrupt context for each interrupt line
 */
static gpio_isr_ctx_t isr_ctx[ISR_NUMOF];


static msp_port_e_t *_port_e(gpio_t pin)
{
    switch (pin >> 8) {
        case 1:
            return PORT_1;
        case 3:
            return PORT_3;
        case 5:
            return PORT_5;
        case 7:
            return PORT_7;
        case 9:
            return PORT_9;
        default:
            return NULL;
    }
}

static msp_port_o_t *_port_o(gpio_t pin)
{
    switch (pin >> 8) {
        case 2:
            return PORT_2;
        case 4:
            return PORT_4;
        case 6:
            return PORT_6;
        case 8:
            return PORT_8;
        case 10:
            return PORT_10;
        default:
            return NULL;
    }
}

static inline msp_port_isr_e_t *_isr_port_e(gpio_t pin)
{
    msp_port_e_t *p = _port_e(pin);

    if ((p == PORT_1)) {
        return (msp_port_isr_e_t *)p;
    }

    return NULL;
}

static inline msp_port_isr_o_t *_isr_port_o(gpio_t pin)
{
    msp_port_o_t *p = _port_o(pin);

    if ((p == PORT_2)) {
        return (msp_port_isr_o_t *)p;
    }

    return NULL;
}


static inline uint8_t _pin(gpio_t pin)
{
    return (uint8_t)(pin & 0xff);
}

static int _ctx(gpio_t pin)
{
    int i = bitarithm_lsb(_pin(pin));

    return (_port_e(pin) == PORT_1) ? i : (i + 8);
}

int gpio_init(gpio_t pin, gpio_mode_t mode)
{
    msp_port_e_t *port_e = _port_e(pin);
    msp_port_o_t *port_o = _port_o(pin);

    /* check if port is valid and mode applicable */
    if ((port_e == NULL && port_o == NULL) || ((mode != GPIO_IN) && (mode != GPIO_OUT))) {
        return -1;
    }

    /* reset pin and output value */

    if (port_e != NULL) {
		if (mode == GPIO_OUT) {
			port_e->DIR |= _pin(pin);
		}
		else {
			port_e->DIR &= ~(_pin(pin));
		}

		port_e->OD &= ~(_pin(pin));
    } else {
		if (mode == GPIO_OUT) {
			port_o->DIR |= _pin(pin);
		}
		else {
			port_o->DIR &= ~(_pin(pin));
		}

		port_o->OD &= ~(_pin(pin));
    }

    return 0;
}

int gpio_init_int(gpio_t pin, gpio_mode_t mode, gpio_flank_t flank,
                    gpio_cb_t cb, void *arg)
{
    msp_port_isr_e_t *port_e = _isr_port_e(pin);
    msp_port_isr_o_t *port_o = _isr_port_o(pin);

    /* check if port, pull resistor and flank configuration are valid */
    if ((port_e == NULL && port_o == NULL) || (flank == GPIO_BOTH)) {
        return -1;
    }

    /* disable any activated interrupt */
    if (port_e != NULL) {
		port_e->IE &= ~(_pin(pin));

		/* configure as input */
		if (gpio_init(pin, mode) < 0) {
			return -1;
		}

		/* save ISR context */
		isr_ctx[_ctx(pin)].cb = cb;
		isr_ctx[_ctx(pin)].arg = arg;

		/* configure flank */
		port_e->IES &= ~(_pin(pin));
		port_e->IES |= (flank & _pin(pin));

		/* clear pending interrupts and enable the IRQ */
		port_e->IFG &= ~(_pin(pin));
    } else {
    	port_o->IE &= ~(_pin(pin));

		/* configure as input */
		if (gpio_init(pin, mode) < 0) {
			return -1;
		}

		/* save ISR context */
		isr_ctx[_ctx(pin)].cb = cb;
		isr_ctx[_ctx(pin)].arg = arg;

		/* configure flank */
		port_o->IES &= ~(_pin(pin));
		port_o->IES |= (flank & _pin(pin));

		/* clear pending interrupts and enable the IRQ */
		port_o->IFG &= ~(_pin(pin));
    }

    gpio_irq_enable(pin);

    return 0;
}

void gpio_periph_mode(gpio_t pin, bool enable)
{
    REG8 *sel;

    msp_port_e_t *port_e = _port_e(pin);
    msp_port_o_t *port_o = _port_o(pin);

    if (port_e) {
        sel = &(port_e->SEL);
    } else if (port_o) {
    	sel = &(port_o->SEL);
    } else {
    	return;
    }

    if (enable) {
        *sel |= _pin(pin);
    }
    else {
        *sel &= ~(_pin(pin));
    }
}

void gpio_irq_enable(gpio_t pin)
{
    msp_port_isr_e_t *port_e = _isr_port_e(pin);
    msp_port_isr_o_t *port_o = _isr_port_o(pin);

    if (port_e) {
        port_e->IE |= _pin(pin);
    }

    if (port_o) {
    	port_o->IE |= _pin(pin);
    }
}

void gpio_irq_disable(gpio_t pin)
{
	msp_port_isr_e_t *port_e = _isr_port_e(pin);
	msp_port_isr_o_t *port_o = _isr_port_o(pin);

    if (port_e) {
        port_e->IE &= ~(_pin(pin));
    }

    if (port_o) {
		port_o->IE &= ~(_pin(pin));
	}
}

int gpio_read(gpio_t pin)
{
    msp_port_e_t *port_e = _port_e(pin);
    msp_port_o_t *port_o = _port_o(pin);

    if (port_e) {
		if (port_e->DIR & _pin(pin)) {
			return (int)(port_e->OD & _pin(pin));
		}
		else {
			return (int)(port_e->IN & _pin(pin));
		}
    }

    if (port_o) {
		if (port_o->DIR & _pin(pin)) {
			return (int)(port_o->OD & _pin(pin));
		}
		else {
			return (int)(port_o->IN & _pin(pin));
		}
	}

    return -1;
}

void gpio_set(gpio_t pin)
{
	msp_port_e_t *port_e = _port_e(pin);

	if (port_e) {
		port_e->OD |= _pin(pin);
	} else {
		msp_port_o_t *port_o = _port_o(pin);

		if (port_o) {
			port_o->OD |= _pin(pin);
		}
	}
}

void gpio_clear(gpio_t pin)
{
	msp_port_e_t *port_e = _port_e(pin);

	if (port_e) {
		port_e->OD &= ~(_pin(pin));
	} else {
		msp_port_o_t *port_o = _port_o(pin);

		if (port_o) {
			port_o->OD &= ~(_pin(pin));
		}
	}
}

void gpio_toggle(gpio_t pin)
{
	msp_port_e_t *port_e = _port_e(pin);

	if (port_e) {
		port_e->OD ^= _pin(pin);
	} else {
		msp_port_o_t *port_o = _port_o(pin);

		if (port_o) {
			port_o->OD ^= _pin(pin);
		}
	}
}

void gpio_write(gpio_t pin, int value)
{
	REG8 *od;

	msp_port_e_t *port_e = _port_e(pin);
	msp_port_o_t *port_o = _port_o(pin);

	if (port_e) {
		od = &(port_e->OD);
	} else if (port_o) {
		od = &(port_o->OD);
	} else {
		return;
	}

    if (value) {
        *(od) |= _pin(pin);
    }
    else {
    	*(od) &= ~(_pin(pin));
    }
}

static inline void isr_handler_e(msp_port_isr_e_t *port, int ctx)
{
    for (int i = 0; i < PINS_PER_PORT; i++) {
        if ((port->IE & (1 << i)) && (port->IFG & (1 << i))) {
            port->IFG &= ~(1 << i);
            isr_ctx[i + ctx].cb(isr_ctx[i + ctx].arg);
        }
    }
}

static inline void isr_handler_o(msp_port_isr_o_t *port, int ctx)
{
    for (int i = 0; i < PINS_PER_PORT; i++) {
        if ((port->IE & (1 << i)) && (port->IFG & (1 << i))) {
            port->IFG &= ~(1 << i);
            isr_ctx[i + ctx].cb(isr_ctx[i + ctx].arg);
        }
    }
}

ISR(PORT1_VECTOR, isr_port1)
{
    __enter_isr();
    isr_handler_e((msp_port_isr_e_t *)PORT_1, 0);
    __exit_isr();
}

ISR(PORT2_VECTOR, isr_port2)
{
    __enter_isr();
    isr_handler_o((msp_port_isr_o_t *)PORT_2, 8);
    __exit_isr();
}
