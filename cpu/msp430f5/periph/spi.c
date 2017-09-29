/*
 * Copyright (C) 2015-2016 Freie Universität Berlin
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_msp430fxyz
 * @ingroup     drivers_periph_spi
 * @{
 *
 * @file
 * @brief       Low-level SPI driver implementation
 *
 * This SPI driver implementation does only support one single SPI device for
 * now. This is sufficient, as most MSP430 CPU's only support two serial
 * devices - one used as UART and one as SPI.
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 *
 * @}
 */

#include "cpu.h"
#include "mutex.h"
#include "assert.h"
#include "periph/spi.h"

/**
 * @brief   Mutex for locking the SPI device
 */
static mutex_t spi_lock[SPI_NUMOF];

static msp_spi_conf_t msp_spi_conf[SPI_NUMOF] = SPI_CONF;

void spi_init(spi_t bus)
{
    assert(bus <= SPI_NUMOF);

    /* put SPI device in reset state */
    msp_spi_conf_t* conf = &msp_spi_conf[bus];

    conf->base->CTL1 = USCI_SPI_CTL1_SWRST;
    conf->base->CTL1 |= (USCI_SPI_CTL1_SSEL_SMCLK);

    /* trigger the pin configuration */
    spi_init_pins(bus);

    mutex_init(&spi_lock[bus]);
}

void spi_init_pins(spi_t bus)
{
	assert(bus <= SPI_NUMOF);

	/* put SPI device in reset state */
	msp_spi_conf_t* conf = &msp_spi_conf[bus];

    gpio_periph_mode(conf->miso, true);
    gpio_periph_mode(conf->mosi, true);
    gpio_periph_mode(conf->clk, true);
}

int spi_acquire(spi_t bus, spi_cs_t cs, spi_mode_t mode, spi_clk_t clk)
{
	assert(bus <= SPI_NUMOF);

	/* put SPI device in reset state */
	msp_spi_conf_t* conf = &msp_spi_conf[bus];

    if (clk == SPI_CLK_10MHZ) {
        return SPI_NOCLK;
    }

    /* lock the bus */
    mutex_lock(&(spi_lock[bus]));

    /* calculate baudrate */
    uint32_t br = CLOCK_CMCLK / clk;
    /* make sure the is not smaller then 2 */
    if (br < 2) {
        br = 2;
    }
    conf->base->BR0 = (uint8_t)br;
    conf->base->BR1 = (uint8_t)(br >> 8);

    /* configure bus mode */
    /* configure mode */
    conf->base->CTL0 = (USCI_SPI_CTL0_UCSYNC | USCI_SPI_CTL0_MST|
                     USCI_SPI_CTL0_MODE_0 | USCI_SPI_CTL0_MSB | mode);
    /* release from software reset */
    conf->base->CTL1 &= ~(USCI_SPI_CTL1_SWRST);

    return SPI_OK;
}

void spi_release(spi_t bus)
{
	assert(bus <= SPI_NUMOF);

	/* put SPI device in reset state */
	msp_spi_conf_t* conf = &msp_spi_conf[bus];

    /* put SPI device back in reset state */
	conf->base->CTL1 |= (USCI_SPI_CTL1_SWRST);

    /* release the bus */
    mutex_unlock(&(spi_lock[bus]));
}

void spi_transfer_bytes(spi_t bus, spi_cs_t cs, bool cont,
                        const void *out, void *in, size_t len)
{
	assert(bus <= SPI_NUMOF);

	/* put SPI device in reset state */
	msp_spi_conf_t* conf = &msp_spi_conf[bus];

    const uint8_t *out_buf = out;
    uint8_t *in_buf = in;

    assert(out_buf || in_buf);

    if (cs != SPI_CS_UNDEF) {
        gpio_clear((gpio_t)cs);
    }

    /* if we only send out data, we do this the fast way... */
    if (!in_buf) {
        for (size_t i = 0; i < len; i++) {
            while (!(conf->base->IFG & SPI_IE_TX_BIT)) {}

            conf->base->TXBUF = out_buf[i];
        }

        /* finally we need to wait, until all transfers are complete */
        while (conf->base->STAT & USCI_SPI_STAT_UCBUSY) {}

        conf->base->RXBUF;
    }
    else if (!out_buf) {
        for (size_t i = 0; i < len; i++) {
        	conf->base->TXBUF = 0;

            while (!(conf->base->IFG & SPI_IE_RX_BIT)) {}

            in_buf[i] = (char)conf->base->RXBUF;
        }
    }
    else {
        for (size_t i = 0; i < len; i++) {
            while (!(conf->base->IFG & SPI_IE_TX_BIT)) {}

            conf->base->TXBUF = out_buf[i];

            while (!(conf->base->IFG & SPI_IE_RX_BIT)) {}

            in_buf[i] = (char)conf->base->RXBUF;
        }
    }

    if ((!cont) && (cs != SPI_CS_UNDEF)) {
        gpio_set((gpio_t)cs);
    }
}
