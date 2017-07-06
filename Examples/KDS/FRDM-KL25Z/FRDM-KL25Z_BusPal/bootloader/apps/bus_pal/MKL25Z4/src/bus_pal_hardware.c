/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "bus_pal_hardware.h"
#include "fpga_clock_registers.h"
#include "fsl_device_registers.h"
#include "i2c/fsl_i2c.h"
#include "microseconds/microseconds.h"
#include "spi/fsl_spi.h"
#include "lpsci/fsl_lpsci.h"

////////////////////////////////////////////////////////////////////////////////
// Prototypes
////////////////////////////////////////////////////////////////////////////////

/*!
 * @brief init uart functions.
 */
static void init_uarts(void);

/*!
 * @brief dspi initialization.
 */
static void init_spi(void);

/*!
 * @brief i2c initialization.
 */
static void init_i2c(uint32_t instance);

/*!
 * @brief i2c de-initialization.
 */
static void deinit_i2c(uint32_t instance);

/*!
 * @brief uart rx callback function.
 */
static void uart_rx_callback(uint8_t byte);

/*!
 * @brief get PORT base address function.
 */
static PORT_Type *getPortBaseAddrFromAscii(uint8_t port);

/*!
 * @brief get GPIO base address function.
 */
static GPIO_Type *getGpioBaseAddrFromAscii(uint8_t port);

/*!
 * @brief fpga write clock reg function.
 */
static void write_fpga_clock_reg(uint8_t reg, uint8_t val);

////////////////////////////////////////////////////////////////////////////////
// Variables
////////////////////////////////////////////////////////////////////////////////

//! @brief Variable for i2c host configuration information
static i2c_user_config_t s_i2cUserConfig = {.slaveAddress = 0x10, //!< The slave's 7-bit address
                                            .baudRate_kbps = 100 };

static i2c_user_config_t s_i2cFPGAUserConfig = {.slaveAddress = CY22393_ADDR, //!< The slave's 7-bit address
                                                .baudRate_kbps = 400 };

static spi_user_config_t s_spiUserConfig = {.polarity = kSPI_ClockPolarityActiveLow, /*!< Clock polarity */
                                            .phase = kSPI_ClockPhaseSecondEdge,      /*!< Clock phase */
                                            .direction = kSPI_MsbFirst,              /*!< MSB or LSB */
                                            .baudRate_Bps = 100000,                  /*!< Baud Rate for SPI in Hz */
                                            .clock_Hz = 0 };

static spi_master_handle_t s_spiHandle;
static i2c_master_handle_t s_i2cHandle;

//! @brief Variable for host data receiving
static uint8_t *s_rxData;
static uint32_t s_bytesRx;

const static uint32_t g_spiBaseAddr[] = SPI_BASE_ADDRS;
const static uint32_t g_i2cBaseAddr[] = I2C_BASE_ADDRS;
const static uint32_t g_lpsciBaseAddr[] = UART0_BASE_ADDRS;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

/*FUNCTION**********************************************************************
 *
 * Function Name : get_bus_clock
 * Description   : Gets bus clock
 *
 *END**************************************************************************/
uint32_t get_bus_clock(void)
{
    uint32_t busClockDivider = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1;
    return (SystemCoreClock / busClockDivider);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : init_hardware
 * Description   : hardware initialization
 *
 *END**************************************************************************/
void init_hardware(void)
{
    /* SIM->SCGC5: PORTA=1 */
    SIM->SCGC5 |= (uint32_t)0x0200UL;      /* Enable clock gate for ports to enable pin routing */
                                           /* SIM->CLKDIV1:
                                            * OUTDIV1=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,OUTDIV4=1,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0,??=0
                                            */
    SIM->CLKDIV1 = (uint32_t)0x10010000UL; /* Update system prescalers */
    /* PORTA->PCR18: ISF=0,MUX=0 */
    PORTA->PCR[18] &= (uint32_t)~0x01000700UL;
    /* PORTA->PCR19: ISF=0,MUX=0 */
    PORTA->PCR[19] &= (uint32_t)~0x01000700UL;
    /* Switch to FBE Mode */
    /* OSC0->CR: ERCLKEN=1,??=0,EREFSTEN=0,??=0,SC2P=1,SC4P=0,SC8P=0,SC16P=1 */
    OSC0->CR = (uint8_t)0x89U;
    /* MCG->C2: LOCRE0=0,??=0,RANGE0=2,HGO0=0,EREFS0=1,LP=0,IRCS=0 */
    MCG->C2 = (uint8_t)0x24U;
    /* MCG->C1: CLKS=2,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
    MCG->C1 = (uint8_t)0x9AU;
    /* MCG->C4: DMX32=0,DRST_DRS=0 */
    MCG->C4 &= (uint8_t) ~(uint8_t)0xE0U;
    /* MCG->C5: ??=0,PLLCLKEN0=0,PLLSTEN0=0,PRDIV0=1 */
    MCG->C5 = (uint8_t)0x01U;
    /* MCG->C6: LOLIE0=0,PLLS=0,CME0=0,VDIV0=0 */
    MCG->C6 = (uint8_t)0x00U;
    while ((MCG->S & MCG_S_IREFST_MASK) != 0x00U)
    { /* Check that the source of the FLL reference clock is the external reference clock. */
    }
    while ((MCG->S & 0x0CU) != 0x08U)
    { /* Wait until external reference clock is selected as MCG output */
    }
    /* Switch to PBE Mode */
    /* MCG->C6: LOLIE0=0,PLLS=1,CME0=0,VDIV0=0 */
    MCG->C6 = (uint8_t)0x40U;
    while ((MCG->S & 0x0CU) != 0x08U)
    { /* Wait until external reference clock is selected as MCG output */
    }
    while ((MCG->S & MCG_S_LOCK0_MASK) == 0x00U)
    { /* Wait until locked */
    }
    /* Switch to PEE Mode */
    /* MCG->C1: CLKS=0,FRDIV=3,IREFS=0,IRCLKEN=1,IREFSTEN=0 */
    MCG->C1 = (uint8_t)0x1AU;
    while ((MCG->S & 0x0CU) != 0x0CU)
    { /* Wait until output of the PLL is selected */
    }

    SIM->SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK | SIM_SCGC5_PORTD_MASK |
                   SIM_SCGC5_PORTE_MASK);

    SIM->SOPT2 |= SIM_SOPT2_PLLFLLSEL_MASK // set PLLFLLSEL to select the PLL for this clock source
                  | SIM_SOPT2_UART0SRC(1); // select the PLLFLLCLK as UART0 clock source

    // Enable the pins for the selected UART
    // Enable the UART_TXD function on PTA1
    PORTA->PCR[1] = PORT_PCR_MUX(0x2);
    // Enable the UART_TXD function on PTA2
    PORTA->PCR[2] = PORT_PCR_MUX(0x2);

    // Enable pins for UART1.
    PORTC->PCR[3] = PORT_PCR_MUX(3); // UART1_RX is ALT3 for pin PTC3
    PORTC->PCR[4] = PORT_PCR_MUX(3); // UART1_TX is ALT3 for pin PTC4

    // Enable pins for I2C0.
    PORTC->PCR[8] = PORT_PCR_MUX(2); // I2C0_SCL is ALT2 for pin PTC8
    PORTC->PCR[9] = PORT_PCR_MUX(2); // I2C0_SDA is ALT2 for pin PTC9

    // Enable pins for I2C1.
    PORTE->PCR[0] = PORT_PCR_MUX(6); // I2C1_SDA is ALT6 for pin PTE0
    PORTE->PCR[1] = PORT_PCR_MUX(6); // I2C1_SCL is ALT6 for pin PTE1

    // Enable pins for SPI0 on PTD0~3 (not available on 32-pin QFN package)
    PORTD->PCR[0] = PORT_PCR_MUX(2); // SPI0_PCS0 is ALT2 for pin PTD0
    PORTD->PCR[1] = PORT_PCR_MUX(2); // SPI0_SCK is ALT2 for pin PTD1
    PORTD->PCR[2] = PORT_PCR_MUX(2); // SPI0_MOSI is ALT2 for pin PTD2
    PORTD->PCR[3] = PORT_PCR_MUX(2); // SPI0_MISO is ALT2 for pin PTD3

    // Ungate clocks to the UART modules
    SIM->SCGC4 |= (SIM_SCGC4_UART0_MASK | SIM_SCGC4_UART1_MASK | SIM_SCGC4_UART2_MASK);

    microseconds_init();

    init_uarts();
    init_spi();
    init_i2c(0);
    init_i2c(1);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : uart0_get_clock
 * Description   : get uart0 clock
 *
 *END**************************************************************************/
uint32_t uart0_get_clock(uint32_t instance)
{
    switch (instance)
    {
        case 0:
        {
            return (((CPU_XTAL_CLK_HZ * 24) / 2) / 2);
        }
        case 1:
        {
            // UART1 always uses the system clock / OUTDIV4
            const uint32_t busClockDivider =
                ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1;
            return (SystemCoreClock / busClockDivider);
        }
        case 2:
        {
            // UART2 always uses the system clock / OUTDIV4
            uint32_t busClockDivider = ((SIM->CLKDIV1 & SIM_CLKDIV1_OUTDIV4_MASK) >> SIM_CLKDIV1_OUTDIV4_SHIFT) + 1;
            return (SystemCoreClock / busClockDivider);
        }
        default:
            return 0;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : init_uarts
 * Description   : Initialize UART ports
 *
 *END**************************************************************************/
static void init_uarts(void)
{
    lpsci_config_t config;
    uint32_t baseAddr = g_lpsciBaseAddr[0];

    LPSCI_GetDefaultConfig(&config);

    config.baudRate_Bps = 57600;
    config.enableRx = true;
    config.enableTx = true;

    LPSCI_Init((UART0_Type *)baseAddr, &config, uart0_get_clock(0));
    LPSCI_EnableInterrupts((UART0_Type *)baseAddr, kLPSCI_RxDataRegFullInterruptEnable);
    NVIC_EnableIRQ(UART0_IRQn);
}

/********************************************************************/
/*
 * UART0 IRQ Handler
 *
 */
void UART0_IRQHandler(void)
{
    uart_rx_callback(UART0->D);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : write_fpga_clock_reg
 * Description   : fpga clock reg write function
 *
 *END**************************************************************************/
void write_fpga_clock_reg(uint8_t reg, uint8_t val)
{
    uint8_t packet[2] = { reg, val };
    uint32_t baseAddr = g_lpsciBaseAddr[0];

    i2c_master_transfer_t send_data;
    send_data.slaveAddress = s_i2cFPGAUserConfig.slaveAddress;
    send_data.direction = kI2C_Write;
    send_data.data = packet;
    send_data.dataSize = 2;

    I2C_MasterTransferBlocking((I2C_Type *)baseAddr, &send_data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : set_fpga_clock
 * Description   : fpga clock set function
 *
 *END**************************************************************************/
void set_fpga_clock(uint32_t clock)
{
    uint32_t i;
    uint32_t P, bestP;
    uint32_t Q, bestQ;
    uint32_t realClock;
    uint32_t diff, min_diff;
    uint32_t PHigh, P0;
    uint32_t pumpVal;
    uint32_t vcoClock;
    uint32_t postDiv;

    // Get the closest we can to the max VCO clock
    vcoClock = clock * (CY22393_MAX_VCO_CLK / clock);
    // Get the post divider we will need after setting to this high clock
    postDiv = vcoClock / clock;

    // The post div value cannot be above 31 for VCO clocks above 333MHZ
    if (postDiv > CY22393_POSTDIV_MAX_VAL)
    {
        uint32_t correction = postDiv - CY22393_POSTDIV_MAX_VAL;
        vcoClock = CY22393_MAX_VCO_CLK - (clock * correction);
        postDiv = CY22393_POSTDIV_MAX_VAL;
    }

    /* http://www.cypress.com/?id=4&rID=27709 */
    /* In all for loops, if min_diff = 0, exit for loop */
    /* F = (Ref * (P/Q)) / postDiv */
    /* Ref / Q must be >= 250khz */
    /* Q range can be between 2 and 257 */
    /* P range can be between 16 and 1600 */
    /* find combination of p0, p, and q resulting in clock closest to the requested value */
    min_diff = ~0;
    bestP = 0;
    bestQ = 0;

    for (Q = 2; ((CY22393_REF_CLK / Q) >= CY22393_MIN_REF_DIV_Q) && (Q < 257) && min_diff; Q++)
    {
        for (P = 16; (P <= 1600) && min_diff; P++)
        {
            realClock = (CY22393_REF_CLK / Q) * P;

            if (vcoClock >= realClock)
            {
                diff = vcoClock - realClock;
            }
            else
            {
                diff = realClock - vcoClock;
            }

            if (min_diff > diff)
            {
                /* a better match found */
                min_diff = diff;
                bestP = P;
                bestQ = Q;
            }

            // Since we are just increasing our multiplier in this loop if its past our desired clock
            // we can break to start increasing the quotient
            if (realClock > vcoClock)
            {
                break;
            }
        }
    }

    P0 = bestP & 1;
    PHigh = (bestP / 2) - 3;
    bestQ -= 2;

    if ((bestP >= 16) && (bestP <= 231))
    {
        pumpVal = 0;
    }
    else if ((bestP >= 232) && (bestP <= 626))
    {
        pumpVal = 1;
    }
    else if ((bestP >= 627) && (bestP <= 834))
    {
        pumpVal = 2;
    }
    else if ((bestP >= 835) && (bestP <= 1043))
    {
        pumpVal = 3;
    }
    else
    {
        pumpVal = 4;
    }

    // Clear any existing values
    for (i = CY22393_REG_LOW; i <= CY22393_REG_HIGH; i++)
    {
        write_fpga_clock_reg(i, 0);
    }

    // Disable PLL3
    write_fpga_clock_reg(CY22393_REG_PLL3E, 0);

    // Enable Clock A
    write_fpga_clock_reg(CY22393_REG_CLKA_DIVIDE, 1);

    // Set the CLK A post divider
    write_fpga_clock_reg(CY22393_REG_CLKA_DIVIDE, postDiv);

    // Disable the other clock outputs
    write_fpga_clock_reg(CY22393_REG_CLKB_DIVIDE, CY22393_DIVIDE_OFF); // clkb
    write_fpga_clock_reg(CY22393_REG_CLKC_DIVIDE, CY22393_DIVIDE_OFF); // clkc
    write_fpga_clock_reg(CY22393_REG_CLKD_DIVIDE, CY22393_DIVIDE_OFF); // clkd

    // Set all clock sources from PLL3
    write_fpga_clock_reg(CY22393_REG_SOURCE, 0xFF);

    // Set All clocks ACAdj to nominal (b01) with pulldowns enabled and xbuf output enable
    write_fpga_clock_reg(CY22393_REG_AC, 0x5C);
    // Set all clocks to use nominal drive strength
    write_fpga_clock_reg(CY22393_REG_DC, CY22393_DC);

    write_fpga_clock_reg(CY22393_REG_PLL3P, PHigh);
    write_fpga_clock_reg(CY22393_REG_PLL3Q, bestQ);

    // B6 enables PLL3
    // B5:B3 is the pump value
    // B2 is for P0 value
    // B1:0 is for B9:8 of P
    write_fpga_clock_reg(CY22393_REG_PLL3E, (1 << 6) | (pumpVal << 3) | (P0 << 2) | ((PHigh & 0x300) >> 8));
}

/*FUNCTION**********************************************************************
 *
 * Function Name : init_spi
 * Description   : spi init function
 *
 *END**************************************************************************/

void init_spi(void)
{
    spi_master_config_t config;
    uint32_t baseAddr = g_spiBaseAddr[0];

    SPI_MasterGetDefaultConfig(&config);

    config.polarity = s_spiUserConfig.polarity;
    config.phase = s_spiUserConfig.phase;
    config.baudRate_Bps = s_spiUserConfig.baudRate_Bps;
    s_spiUserConfig.clock_Hz = get_bus_clock();

    SPI_MasterInit((SPI_Type *)baseAddr, &config, s_spiUserConfig.clock_Hz);
    SPI_MasterTransferCreateHandle((SPI_Type *)baseAddr, &s_spiHandle, NULL, NULL);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : init_i2c
 * Description   : I2C init function
 *
 *END**************************************************************************/

void init_i2c(uint32_t instance)
{
    uint32_t baseAddr = g_i2cBaseAddr[instance];
    i2c_master_config_t config;

    I2C_MasterGetDefaultConfig(&config);

    I2C_MasterInit((I2C_Type *)baseAddr, &config, get_bus_clock());
    I2C_MasterTransferCreateHandle((I2C_Type *)baseAddr, &s_i2cHandle, NULL, NULL);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : deinit_i2c
 * Description   : I2C de-init function
 *
 *END**************************************************************************/
void deinit_i2c(uint32_t instance)
{
    uint32_t baseAddr = g_i2cBaseAddr[instance];
    I2C_MasterDeinit((I2C_Type *)baseAddr);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : host_start_command_rx
 * Description   : receiving host start command process
 *
 *END**************************************************************************/
void host_start_command_rx(uint8_t *dest, uint32_t length)
{
    s_rxData = dest;
    s_bytesRx = 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : host_stop_command_rx
 * Description   : receiving host stop command process
 *
 *END**************************************************************************/
void host_stop_command_rx(void)
{
    s_rxData = 0;
    s_bytesRx = 0;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : get_bytes_received_from_host
 * Description   : receiving host get bytes command process
 *
 *END**************************************************************************/
uint32_t get_bytes_received_from_host(void)
{
    return s_bytesRx;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : write_bytes_to_host
 * Description   : sending host bytes command process
 *
 *END**************************************************************************/
void write_bytes_to_host(uint8_t *src, uint32_t length)
{
    uint32_t baseAddr = g_lpsciBaseAddr[0];

    LPSCI_TransferSendBlocking((UART0_Type *)baseAddr, src, length);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_i2c_address
 * Description   : i2c config address process
 *
 *END**************************************************************************/
void configure_i2c_address(uint8_t address)
{
    s_i2cUserConfig.slaveAddress = address;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_i2c_speed
 * Description   : i2c config speed process
 *
 *END**************************************************************************/
void configure_i2c_speed(uint32_t speedkhz)
{
    s_i2cUserConfig.baudRate_kbps = speedkhz;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : send_spi_data
 * Description   : spi send data proces
 *
 *END**************************************************************************/
void send_spi_data(uint8_t *src, uint32_t writeLength)
{
    spi_transfer_t send_data;
    uint32_t baseAddr = g_spiBaseAddr[0];

    send_data.txData = src;
    send_data.dataSize = writeLength;
    send_data.rxData = NULL;
    SPI_MasterTransferBlocking((SPI_Type *)baseAddr, &send_data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : receive_spi_data
 * Description   : spi receiving data process
 *
 *END**************************************************************************/
void receive_spi_data(uint8_t *dest, uint32_t readLength)
{
    spi_transfer_t receive_data;
    uint32_t baseAddr = g_spiBaseAddr[0];

    receive_data.rxData = dest;
    receive_data.dataSize = readLength;
    receive_data.txData = NULL;
    SPI_MasterTransferBlocking((SPI_Type *)baseAddr, &receive_data);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_spi_speed
 * Description   : spi config speed process
 *
 *END**************************************************************************/
void configure_spi_speed(uint32_t speedkhz)
{
    s_spiUserConfig.baudRate_Bps = speedkhz * 1000;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_spi_settings
 * Description   : spi config settings process
 *
 *END**************************************************************************/
void configure_spi_settings(spi_clock_polarity_t polarity, spi_clock_phase_t phase, spi_shift_direction_t direction)
{
    s_spiUserConfig.polarity = polarity;
    s_spiUserConfig.phase = phase;
    s_spiUserConfig.direction = direction;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : send_i2c_data
 * Description   : i2c sending data process
 *
 *END**************************************************************************/
status_t send_i2c_data(uint8_t *src, uint32_t writeLength)
{
    i2c_master_transfer_t send_data;
    uint32_t baseAddr = g_i2cBaseAddr[0];
    send_data.slaveAddress = s_i2cUserConfig.slaveAddress;
    send_data.direction = kI2C_Write;
    send_data.data = src;
    send_data.dataSize = writeLength;

    if (I2C_MasterTransferBlocking((I2C_Type *)baseAddr, &send_data) != kStatus_Success)
    {
        deinit_i2c(0);
        init_i2c(0);
        return kStatus_Fail;
    }

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : receive_i2c_data
 * Description   : i2c receiving data process
 *
 *END**************************************************************************/
status_t receive_i2c_data(uint8_t *dest, uint32_t readLength)
{
    i2c_master_transfer_t receive_data;
    uint32_t baseAddr = g_i2cBaseAddr[0];
    receive_data.slaveAddress = s_i2cUserConfig.slaveAddress;
    receive_data.direction = kI2C_Read;
    receive_data.data = dest;
    receive_data.dataSize = readLength;

    if (I2C_MasterTransferBlocking((I2C_Type *)baseAddr, &receive_data) != kStatus_Success)
    {
        deinit_i2c(0);
        init_i2c(0);
        return kStatus_Fail;
    }

    return kStatus_Success;
}

/*FUNCTION**********************************************************************
 *
 * Function Name : uart_rx_callback
 * Description   : uart callback function
 *
 *END**************************************************************************/
void uart_rx_callback(uint8_t byte)
{
    if (s_rxData)
    {
        s_rxData[s_bytesRx++] = byte;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : getPortBaseAddrFromAscii
 * Description   : PORT get base address function
 *
 *END**************************************************************************/
PORT_Type *getPortBaseAddrFromAscii(uint8_t port)
{
    if ((port >= 'a') && (port <= 'e'))
    {
        port = port - 'a';
    }
    else if ((port >= 'A') && (port <= 'E'))
    {
        port = port - 'A';
    }

    switch (port)
    {
        default:
        case 0:
            return PORTA;
        case 1:
            return PORTB;
        case 2:
            return PORTC;
        case 3:
            return PORTD;
        case 4:
            return PORTE;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : getGpioBaseAddrFromAscii
 * Description   : GPIO get base address function
 *
 *END**************************************************************************/
GPIO_Type *getGpioBaseAddrFromAscii(uint8_t port)
{
    if ((port >= 'a') && (port <= 'e'))
    {
        port = port - 'a';
    }
    else if ((port >= 'A') && (port <= 'E'))
    {
        port = port - 'A';
    }

    switch (port)
    {
        default:
        case 0:
            return GPIOA;
        case 1:
            return GPIOB;
        case 2:
            return GPIOC;
        case 3:
            return GPIOD;
        case 4:
            return GPIOE;
    }
}

/*FUNCTION**********************************************************************
 *
 * Function Name : configure_gpio
 * Description   : GPIO config processing
 *
 *END**************************************************************************/
void configure_gpio(uint8_t port, uint8_t pinNum, uint8_t muxVal)
{
    PORT_Type *realPort = getPortBaseAddrFromAscii(port);
    realPort->PCR[pinNum] = ((~PORT_PCR_MUX_MASK) & realPort->PCR[pinNum]) | PORT_PCR_MUX(muxVal);
}

/*FUNCTION**********************************************************************
 *
 * Function Name : set_gpio
 * Description   : GPIO set up function
 *
 *END**************************************************************************/
void set_gpio(uint8_t port, uint8_t pinNum, uint8_t level)
{
    GPIO_Type *realPort = getGpioBaseAddrFromAscii(port);

    realPort->PDDR |= 1 << pinNum;

    if (level)
    {
        realPort->PSOR |= 1 << pinNum;
    }
    else
    {
        realPort->PCOR |= 1 << pinNum;
    }
}

#if __ICCARM__
/*FUNCTION**********************************************************************
 *
 * Function Name : __write
 * Description   : ICCARM write function implementation
 *
 *END**************************************************************************/
size_t __write(int handle, const unsigned char *buf, size_t size)
{
    return size;
}

#endif // __ICCARM__
////////////////////////////////////////////////////////////////////////////////
// EOF
////////////////////////////////////////////////////////////////////////////////
