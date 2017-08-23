/*
 * Copyright (c) 2013-2015, Freescale Semiconductor, Inc.
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

#include "fsl_device_registers.h"
#include "fsl_common.h"

#include "board.h"
#include "fsl_clock.h"
#include "pin_mux.h"	// added for NTAG middleware
#include "Flash_Adapter.h"

#define ADCDAC_LDO_OVERRIDE (1)

/* FRDM-KW41Z Rev A2 xtal trim */
static const uint8_t mXtalTrimDefault = 0x30;

void hardware_init(void)
{
    uint32_t temp, tempTrim;
    uint8_t revId;
    static uint8_t initialized = 0;
    
    if( !initialized )
    {
        if((PMC->REGSC & PMC_REGSC_ACKISO_MASK) != 0x00U)
        {
            PMC->REGSC |= PMC_REGSC_ACKISO_MASK; /* Release hold with ACKISO:  Only has an effect if recovering from VLLSx.*/
            /*clear power management registers after recovery from vlls*/
            SMC->STOPCTRL &= ~SMC_STOPCTRL_LLSM_MASK;
            SMC->PMCTRL   &= ~(SMC_PMCTRL_STOPM_MASK | SMC_PMCTRL_RUNM_MASK);
        }
        
        /* enable clock for PORTs */
        CLOCK_EnableClock(kCLOCK_PortA);
        CLOCK_EnableClock(kCLOCK_PortB);
        CLOCK_EnableClock(kCLOCK_PortC);
        
        SIM->SCGC6 |= (SIM_SCGC6_DMAMUX_MASK); /* Enable clock to DMA_MUX (SIM module) */
        SIM->SCGC7 |= (SIM_SCGC7_DMA_MASK);
        
        /* Obtain REV ID from SIM */
        revId = (uint8_t)((SIM->SDID & SIM_SDID_REVID_MASK) >> SIM_SDID_REVID_SHIFT);
        
        if(0 == revId)
        {
            tempTrim = RSIM->ANA_TRIM;
            RSIM->ANA_TRIM |= RSIM_ANA_TRIM_BB_LDO_XO_TRIM_MASK; /* max trim for BB LDO for XO */
        }
        
        /* Turn on clocks for the XCVR */
        /* Enable RF OSC in RSIM and wait for ready */
        temp = RSIM->CONTROL;
        temp &= ~RSIM_CONTROL_RF_OSC_EN_MASK;
        RSIM->CONTROL = temp | RSIM_CONTROL_RF_OSC_EN(1);
        /* Prevent XTAL_OUT_EN from generating XTAL_OUT request */
        RSIM->RF_OSC_CTRL |= RSIM_RF_OSC_CTRL_RADIO_EXT_OSC_OVRD_EN_MASK;
        /* wait for RF_OSC_READY */
        while((RSIM->CONTROL & RSIM_CONTROL_RF_OSC_READY_MASK) == 0) {}
        
        if(0 == revId)
        {
            SIM->SCGC5 |= SIM_SCGC5_PHYDIG_MASK;
            XCVR_TSM->OVRD0 |= XCVR_TSM_OVRD0_BB_LDO_ADCDAC_EN_OVRD_EN_MASK | XCVR_TSM_OVRD0_BB_LDO_ADCDAC_EN_OVRD_MASK; /* Force ADC DAC LDO on to prevent BGAP failure */
            /* Reset LDO trim settings */
            RSIM->ANA_TRIM = tempTrim;
        }/* Workaround for Rev 1.0 XTAL startup and ADC analog diagnostics circuitry */
        
        /* Init board clock */
        BOARD_ClockInit();

        /* Init DCDC module */
        BOARD_DCDCInit();
        
#ifdef NTAG_I2C
        /* Init pins of NTAG  - only FD pin */

        BOARD_InitPins(); // added for NTAG middleware

        /* Init I2C pins for NTAG communication */
        configure_i2c_pins(BOARD_I2C_INSTANCE); // added for NTAG middleware
#endif // NTAG_I2C

        /* Install callbacks to handle enter and exit low power */
        #if cPWR_UsePowerDownMode
        BOARD_InstallLowPowerCallbacks();
        #endif

        NV_ReadHWParameters(&gHardwareParameters);
        if(0xFFFFFFFF == gHardwareParameters.xtalTrim)
        {
            gHardwareParameters.xtalTrim = mXtalTrimDefault;
        }
        initialized = 1;
    }
}

/*!
** @}
*/
/*
** ###################################################################
**
**     This file was created by Processor Expert 10.4 [05.10]
**     for the Freescale Kinetis series of microcontrollers.
**
** ###################################################################
*/
