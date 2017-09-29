/*
 * Copyright (C) 2015 Freie Universität Berlin
 *               2017 infotec
 *
 * This file is subject to the terms and conditions of the GNU Lesser
 * General Public License v2.1. See the file LICENSE in the top level
 * directory for more details.
 */

/**
 * @ingroup     cpu_msp430f5
 * @{
 *
 * @file
 * @brief       Definition of MSP430f5 family registers
 *
 * @todo        This file is incomplete, not all registers are listed. Further
 *              There are probably some inconsistencies throughout the MSP430
 *              family which need to be addressed.
 *
 * @author      Hauke Petersen <hauke.petersen@fu-berlin.de>
 * @author      Sven Schoradt <s.schoradt@infotec-edv.de>
 */

#ifndef MSP430_REGS_H
#define MSP430_REGS_H

#include <msp430x54xa.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief   Shortcut to specify 8-bit wide registers
 */
#define REG8                volatile uint8_t

/**
 * @brief   Shortcut to specify 16-bit wide registers
 */
#define REG16               volatile uint16_t

/**
 * @brief   Special function registers
 */
typedef struct {
    REG8    IE1;            /**< interrupt enable 1 */
    REG8    IE2;            /**< interrupt enable 2 */
    REG8    IFG1;           /**< interrupt flag 1 */
    REG8    IFG2;           /**< interrupt flag 2 */
    REG8    ME1;            /**< module enable 1 */
    REG8    ME2;            /**< module enable 2 */
} msp_sfr_t;

/**
 * @brief   Digital I/O Port w/o interrupt functionality (P3-P6)
 */

typedef struct {
    REG8    IN;         /**< input data */
    REG8    :8;
    REG8    OD;         /**< output data */
    REG8    :8;
    REG8    DIR;        /**< pin direction */
    REG8    :8;
    REG8    REN;
    REG8    :8;
    REG8    DS;
    REG8    :8;
    REG8    SEL;        /**< alternative function select */
    REG8    :8;
} msp_port_e_t;

typedef struct {
	REG8    :8;
    REG8    IN;         /**< input data */
    REG8    :8;
    REG8    OD;         /**< output data */
    REG8    :8;
    REG8    DIR;        /**< pin direction */
    REG8    :8;
    REG8    REN;
    REG8    :8;
    REG8    DS;
    REG8    :8;
    REG8    SEL;        /**< alternative function select */
} msp_port_o_t;

/**
 * @brief   Digital I/O Port with interrupt functionality (P1 & P2)
 */
typedef struct {
    REG8    IN;         /**< input data */
    REG8    :8;
    REG8    OD;         /**< output data */
    REG8    :8;
    REG8    DIR;        /**< pin direction */
    REG8    :8;
    REG8    REN;
    REG8    :8;
    REG8    DS;
    REG8    :8;
    REG8    SEL;        /**< alternative function select */
    REG8    :8;
    REG16   :16;
    REG16   IV;
    REG16   :16;
    REG16   :16;
    REG16   :16;
    REG16   :16;
    REG8    IES;
    REG8    :8;
    REG8    IE;
    REG8    :8;
    REG8    IFG;
} msp_port_isr_e_t;

typedef struct {
	REG8    :8;
    REG8    IN;         /**< input data */
    REG8    :8;
    REG8    OD;         /**< output data */
    REG8    :8;
    REG8    DIR;        /**< pin direction */
    REG8    :8;
    REG8    REN;
    REG8    :8;
    REG8    DS;
    REG8    :8;
    REG8    SEL;        /**< alternative function select */
    REG8    :8;
    REG16   :16;
	REG16   :16;
	REG16   :16;
	REG16   :16;
	REG16   :16;
	REG16   :16;
	REG8    IES;
	REG8    :8;
	REG8    IE;
	REG8    :8;
	REG8    IFG;
	REG16   IV;
} msp_port_isr_o_t;

/**
 * @brief   USART (UART, SPI and I2C) registers
 */
typedef struct {
    REG8    CTL;        /**< USART control */
    REG8    TCTL;       /**< transmit control */
    REG8    RCTL;       /**< receive control */
    REG8    MCTL;       /**< modulation control */
    REG8    BR0;        /**< baud rate control 0 */
    REG8    BR1;        /**< baud rate control 1 */
    REG8    RXBUF;      /**< receive buffer */
    REG8    TXBUF;      /**< transmit buffer */
} msp_usart_t;

/**
 * @brief   USCI universal serial control interface registers
 */
typedef struct {
	REG8    CTL1;
	REG8    CTL0;
	REG16   :16;
	REG16   :16;
	REG8    BR0;
	REG8    BR1;
	REG8    MCTL;
	REG8    :8;
	REG8    STAT;
	REG8    :8;
	REG8    RXBUF;
	REG8    :8;
	REG8    TXBUF;
	REG8    :8;
	REG8    ABCTL;
	REG8    :8;
	REG8    IRTCTL;
	REG8    IRRCTL;
	REG16   :16;
	REG16   :16;
	REG16   :16;
	REG16   :16;
	REG8    IE;
	REG8    IFG;
	REG8    IV;
} msp_usci_a_t;

typedef struct {
	REG8    CTL1;
	REG8    CTL0;
	REG16   :16;
	REG16   :16;
	REG8    BR0;
	REG8    BR1;
	REG8    MCTL;
	REG8    :8;
	REG8    STAT;
	REG8    :8;
	REG8    RXBUF;
	REG8    :8;
	REG8    TXBUF;
	REG8    :8;
	REG8    I2COA;
	REG8    :8;
	REG8    :8;
	REG8    :8;
	REG16   :16;
	REG16   :16;
	REG16   :16;
	REG16   :16;
	REG8    IE;
	REG8    IFG;
	REG8    IV;
} msp_usci_b_t;

/**
 * @brief   USCI universal serial control interface registers for SPI
 */
typedef struct {
	REG8    CTL1;
	REG8    CTL0;
	REG16   :16;
	REG16   :16;
	REG8    BR0;
	REG8    BR1;
	REG8    MCTL;
	REG8    :8;
	REG8    STAT;
	REG8    :8;
	REG8    RXBUF;
	REG8    :8;
	REG8    TXBUF;
	REG8    :8;
	REG8    :8;
	REG8    :8;
	REG8    :8;
	REG8    :8;
	REG16   :16;
	REG16   :16;
	REG16   :16;
	REG16   :16;
	REG8    IE;
	REG8    IFG;
	REG8    IV;
} msp_usci_spi_t;


/**
 * @brief   Timer interrupt status registers
 */
typedef struct {
    REG16   TBIV;       /**< TIMER_A interrupt status */
    REG16   reserved[7];    /**< reserved */
    REG16   TAIV;       /**< TIMER_B interrupt status */
} msp_timer_ivec_t;

/**
 * @brief   Timer module registers
 */
typedef struct {
    REG16   CTL;        /**< timer control */
    REG16   CCTL[7];    /**< capture compare channel control */
    REG16   R;          /**< current counter value */
    REG16   CCR[7];     /**< capture compare channel values */
    REG16   EX0;
    REG16   :16;
    REG16   :16;
    REG16   :16;
    REG16   :16;
    REG16   :16;
    REG16   :16;
    REG8    IV;
} msp_timer_t;

/**
 * @brief   USART control register bitmap
 * @{
 */
#define USART_CTL_SWRST             (0x01)
#define USART_CTL_MM                (0x02)
#define USART_CTL_SYNC              (0x04)
#define USART_CTL_LISTEN            (0x08)
#define USART_CTL_CHAR              (0x10)
#define USART_CTL_SPB               (0x20)
#define USART_CTL_PEV               (0x40)
#define USART_CTL_PENA              (0x80)
/** @} */

/**
 * @brief   USART transmit control register bitmap
 * @{
 */
#define USART_TCTL_TXEPT            (0x01)
#define USART_TCTL_STC              (0x02)
#define USART_TCTL_TXWAKE           (0x04)
#define USART_TCTL_URXSE            (0x08)
#define USART_TCTL_SSEL_MASK        (0x30)
#define USART_TCTL_SSEL_UCLKI       (0x00)
#define USART_TCTL_SSEL_ACLK        (0x10)
#define USART_TCTL_SSEL_SMCLK       (0x20)
#define USART_TCTL_CKPL             (0x40)
#define USART_TCTL_CKPH             (0x80)
/** @} */

/**
 * @brief   USART receive control register bitmap
 * @{
 */
#define USART_RCTL_RXERR            (0x01)
#define USART_RCTL_RXWAKE           (0x02)
#define USART_RCTL_URXWIE           (0x04)
#define USART_RCTL_URXEIE           (0x08)
#define USART_RCTL_BRK              (0x10)
#define USART_RCTL_OE               (0x20)
#define USART_RCTL_PE               (0x40)
#define USART_RCTL_FE               (0x80)
/** @} */

/**
 * @brief   USCI control A register 0 bitmap
 * @{
 */
#define USCI_CTL0_UCSYNC           (0x01)
#define USCI_CTL0_MODE_MASK        (0x06)
#define USCI_CTL0_MODE_UART        (0x00)
#define USCI_CTL0_MODE_ILMM        (0x02)
#define USCI_CTL0_MODE_ABMM        (0x04)
#define USCI_CTL0_MODE_UART_ABR    (0x06)
#define USCI_CTL0_SPB              (0x08)
#define USCI_CTL0_7BIT             (0x10)
#define USCI_CTL0_MSB              (0x20)
#define USCI_CTL0_PAR              (0x40)
#define USCI_CTL0_PEN              (0x80)
/** @} */

/**
 * @brief   USCI control register 0 bitmap SPI mode
 * @{
 */
#define USCI_SPI_CTL0_UCSYNC        (0x01)
#define USCI_SPI_CTL0_MODE_3        (0x06)
#define USCI_SPI_CTL0_MODE_0        (0x00)
#define USCI_SPI_CTL0_MODE_1        (0x02)
#define USCI_SPI_CTL0_MODE_2        (0x04)
#define USCI_SPI_CTL0_MST           (0x08)
#define USCI_SPI_CTL0_7BIT          (0x10)
#define USCI_SPI_CTL0_MSB           (0x20)
#define USCI_SPI_CTL0_CKPL          (0x40)
#define USCI_SPI_CTL0_CKPH          (0x80)
/** @} */

/**
 * @brief   USCI status register bitmap SPI mode
 * @{
 */
#define USCI_SPI_STAT_UCBUSY        (0x01)
#define USCI_SPI_STAT_UCOE          (0x20)
#define USCI_SPI_STAT_UCFE          (0x40)
#define USCI_SPI_STAT_UCLISTEN      (0x80)
/** @} */

/**
 * @brief   USCI control A register 1 bitmap
 * @{
 */
#define USCI_CTL1_SWRST            (0x01)
#define USCI_CTL1_TXBRK            (0x02)
#define USCI_CTL1_TXADDR           (0x04)
#define USCI_CTL1_DORM             (0x08)
#define USCI_CTL1_BRKIE            (0x10)
#define USCI_CTL1_RXEIE            (0x20)
#define USCI_CTL1_SSEL_MASK        (0xc0)
#define USCI_CTL1_SSEL_UCLK        (0x00)
#define USCI_CTL1_SSEL_ACLK        (0x40)
#define USCI_CTL1_SSEL_SMCLK       (0xc0)



/** @} */

/**
 * @brief   USCI control register 1 bitmap SPI mode
 * @{
 */
#define USCI_SPI_CTL1_SWRST            (0x01)
#define USCI_SPI_CTL1_SSEL_MASK        (0xc0)
#define USCI_SPI_CTL1_SSEL_NA          (0x00)
#define USCI_SPI_CTL1_SSEL_ACLK        (0x40)
#define USCI_SPI_CTL1_SSEL_SMCLK       (0xc0)
/** @} */

/**
 * @brief   USCI modulation A control register
 * @{
 */
#define USCI_MCTL_OS16             (0x01)
#define USCI_MCTL_BRS_MASK         (0xe0)
#define USCI_MCTL_BRS_SHIFT        (1U)
#define USCI_MCTL_BRF_MASK         (0xf0)
#define USCI_MCTL_BRF_SHIFT        (4U)
/** @} */

/**
 * @brief   USCI status A register bitmap
 * @{
 */
#define USCI_STAT_BUSY             (0x01)
#define USCI_STAT_IDLE             (0x02)
#define USCI_STAT_ADDR             (0x02)
#define USCI_STAT_RXERR            (0x04)
#define USCI_STAT_BRK              (0x08)
#define USCI_STAT_PE               (0x10)
#define USCI_STAT_OE               (0x20)
#define USCI_STAT_FE               (0x40)
#define USCI_STAT_LISTEN           (0x80)
/** @} */

/**
 * @brief   Timer Control register bitmap
 * @{
 */
#define TIMER_CTL_IFG                 (0x0001)
#define TIMER_CTL_IE                  (0x0002)
#define TIMER_CTL_CLR                 (0x0004)
#define TIMER_CTL_MC_MASK             (0x0030)
#define TIMER_CTL_MC_STOP             (0x0000)
#define TIMER_CTL_MC_UP               (0x0010)
#define TIMER_CTL_MC_CONT             (0x0020)
#define TIMER_CTL_MC_UPDOWN           (0x0030)
#define TIMER_CTL_ID_MASK             (0x00c0)
#define TIMER_CTL_ID_DIV1             (0x0000)
#define TIMER_CTL_ID_DIV2             (0x0040)
#define TIMER_CTL_ID_DIV4             (0x0080)
#define TIMER_CTL_ID_DIV8             (0x00c0)
#define TIMER_CTL_TASSEL_MASK         (0x0300)
#define TIMER_CTL_TASSEL_TCLK         (0x0000)
#define TIMER_CTL_TASSEL_ACLK         (0x0100)
#define TIMER_CTL_TASSEL_SMCLK        (0x0200)
#define TIMER_CTL_TASSEL_INV_TCLK     (0x0300)
/** @} */

/**
 * @brief   Timer Channel Control register bitmap
 * @{
 */
#define TIMER_CCTL_CCIFG              (0x0001)
#define TIMER_CCTL_COV                (0x0002)
#define TIMER_CCTL_OUT                (0x0004)
#define TIMER_CCTL_CCI                (0x0008)
#define TIMER_CCTL_CCIE               (0x0010)
#define TIMER_CCTL_OUTMOD_MASK        (0x00e0)
#define TIMER_CCTL_OUTMOD_OUTVAL      (0x0000)
#define TIMER_CCTL_OUTMOD_SET         (0x0020)
#define TIMER_CCTL_OUTMOD_TOG_RESET   (0x0040)
#define TIMER_CCTL_OUTMOD_SET_RESET   (0x0060)
#define TIMER_CCTL_OUTMOD_TOGGLE      (0x0080)
#define TIMER_CCTL_OUTMOD_RESET       (0x00a0)
#define TIMER_CCTL_OUTMOD_TOG_SET     (0x00c0)
#define TIMER_CCTL_OUTMOD_RESET_SET   (0x00e0)
#define TIMER_CCTL_CAP                (0x0100)
#define TIMER_CCTL_CLLD_MASK          (0x0600)
#define TIMER_CCTL_SCS                (0x0800)
#define TIMER_CCTL_CCIS_MASK          (0x3000)
#define TIMER_CCTL_CM_MASK            (0xc000)
/** @} */

/**
 * @brief   Base register address definitions
 * @{
 */
#define SFR_BASE                ((uint16_t)0x0100)

#define PORT_1_BASE             ((uint16_t)0x0200)
#define PORT_2_BASE             ((uint16_t)0x0200)
#define PORT_3_BASE             ((uint16_t)0x0220)
#define PORT_4_BASE             ((uint16_t)0x0220)
#define PORT_5_BASE             ((uint16_t)0x0240)
#define PORT_6_BASE             ((uint16_t)0x0240)
#define PORT_7_BASE             ((uint16_t)0x0260)
#define PORT_8_BASE             ((uint16_t)0x0260)
#define PORT_9_BASE             ((uint16_t)0x0280)
#define PORT_10_BASE            ((uint16_t)0x0280)
#define PORT_11_BASE            ((uint16_t)0x02A0)

#define TIMER_IVEC_BASE         ((uint16_t)0x011e)

#define TIMER_A0_BASE           ((uint16_t)0x0340)
#define TIMER_A1_BASE           ((uint16_t)0x0380)
#define TIMER_B0_BASE           ((uint16_t)0x03C0)

#define WD_BASE                 ((uint16_t)0x0120)

#define USCI_A0_BASE            ((uint16_t)0x05C0)
#define USCI_B0_BASE            ((uint16_t)0x05E0)
#define USCI_A1_BASE            ((uint16_t)0x0600)
#define USCI_B1_BASE            ((uint16_t)0x0620)
#define USCI_A2_BASE            ((uint16_t)0x0640)
#define USCI_B2_BASE            ((uint16_t)0x0660)
#define USCI_A3_BASE            ((uint16_t)0x0680)
#define USCI_B3_BASE            ((uint16_t)0x06A0)
/** @} */

/**
 * @brief   Typing of base register objects
 * @{
 */
#define SFR                     ((msp_sfr_t *)SFR_BASE)

#define PORT_1                  ((msp_port_e_t *)PORT_1_BASE)
#define PORT_2                  ((msp_port_o_t *)PORT_2_BASE)
#define PORT_3                  ((msp_port_e_t *)PORT_3_BASE)
#define PORT_4                  ((msp_port_o_t *)PORT_4_BASE)
#define PORT_5                  ((msp_port_e_t *)PORT_5_BASE)
#define PORT_6                  ((msp_port_o_t *)PORT_6_BASE)
#define PORT_7                  ((msp_port_e_t *)PORT_7_BASE)
#define PORT_8                  ((msp_port_o_t *)PORT_8_BASE)
#define PORT_9                  ((msp_port_e_t *)PORT_9_BASE)
#define PORT_10                 ((msp_port_o_t *)PORT_10_BASE)
#define PORT_11                 ((msp_port_o_t *)PORT_11_BASE)

#define USART_0                 ((msp_usart_t *)USART_0_BASE)
#define USART_1                 ((msp_usart_t *)USART_1_BASE)

#define TIMER_IVEC              ((msp_timer_ivec_t *)TIMER_IVEC_BASE)
#define TIMER_A0                ((msp_timer_t *)TIMER_A0_BASE)
#define TIMER_A1                ((msp_timer_t *)TIMER_A1_BASE)
#define TIMER_B0                ((msp_timer_t *)TIMER_B0_BASE)
#define WD                      ((msp_wd_t *)WD_BASE)

#define USCI_A0                 ((msp_usci_a_t *)USCI_A0_BASE)
#define USCI_B0                 ((msp_usci_b_t *)USCI_B0_BASE)
#define USCI_A1                 ((msp_usci_a_t *)USCI_A1_BASE)
#define USCI_B1                 ((msp_usci_b_t *)USCI_B1_BASE)
#define USCI_A2                 ((msp_usci_a_t *)USCI_A2_BASE)
#define USCI_B2                 ((msp_usci_b_t *)USCI_B2_BASE)
#define USCI_A3                 ((msp_usci_a_t *)USCI_A3_BASE)
#define USCI_B4                 ((msp_usci_b_t *)USCI_B3_BASE)
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* MSP430_REGS_H */
/** @} */
