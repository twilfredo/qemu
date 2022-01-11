
/*
 * QEMU model of the Ibex SPI Controller
 *
 * Copyright (C) 2018 Western Digital
 * Copyright (C) 2018 Wilfred Mallawa <wilfred.mallawa@wdc.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef IBEX_SPI_H
#define IBEX_SPI_H

#include "hw/sysbus.h"
#include "hw/hw.h"
#include "hw/ssi/ssi.h"
#include "qemu/fifo8.h"
#include "qom/object.h"

#define TYPE_IBEX_SPI "ibex-spi"
#define IBEX_SPI(obj) \
    OBJECT_CHECK(IbexSPIState, (obj), TYPE_IBEX_SPI)


/* SPI Registers */
#define IBEX_SPI_INTR_STATE         (0x00 / 4)  //rw
#define IBEX_SPI_INTR_ENABLE        (0x04 / 4)  //rw
#define IBEX_SPI_INTR_TEST          (0x08 / 4)  //wo
#define IBEX_SPI_ALERT_TEST         (0x0c / 4)  //wo
#define IBEX_SPI_CONTROL            (0x10 / 4)  //rw
#define IBEX_SPI_STATUS             (0x14 / 4)  //ro
#define IBEX_SPI_CONFIGOPTS         (0x18 / 4)  //rw
#define IBEX_SPI_CSID               (0x1c / 4)  //rw
#define IBEX_SPI_COMMAND            (0x20 / 4)  //wo
/* RX/TX Modelled by FIFO */
#define IBEX_SPI_RXDATA             (0x24 / 4)  //
#define IBEX_SPI_TXDATA             (0x28 / 4)  //

#define IBEX_SPI_ERROR_ENABLE       (0x2c / 4)  //rw
#define IBEX_SPI_ERROR_STATUS       (0x30 / 4)  //rw
#define IBEX_SPI_EVENT_ENABLE       (0x34 / 4)  //rw

/*  Max Register (Based on addr) */
#define IBEX_SPI_MAX_REGS      (IBEX_SPI_EVENT_ENABLE + 1)

typedef struct {
    /* <private> */
    SysBusDevice parent_obj;

    /* <public> */
    MemoryRegion mmio;
    uint32_t regs[IBEX_SPI_MAX_REGS];
    Fifo8 rx_fifo;
    Fifo8 tx_fifo;

    qemu_irq irq;
    uint8_t cs_width;
    qemu_irq *cs_lines;
    SSIBus *ssi;
} IbexSPIState;

#endif