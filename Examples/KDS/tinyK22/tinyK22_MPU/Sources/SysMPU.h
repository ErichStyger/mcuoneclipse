/*
** ###################################################################
**     Processors:          MK64FN1M0CAJ12
**                          MK64FN1M0VDC12
**                          MK64FN1M0VLL12
**                          MK64FN1M0VLQ12
**                          MK64FN1M0VMD12
**                          MK64FX512VDC12
**                          MK64FX512VLL12
**                          MK64FX512VLQ12
**                          MK64FX512VMD12
**
**     Compilers:           Keil ARM C/C++ Compiler
**                          Freescale C/C++ for Embedded ARM
**                          GNU C Compiler
**                          IAR ANSI C/C++ Compiler for ARM
**                          MCUXpresso Compiler
**
**     Reference manual:    K64P144M120SF5RM, Rev.2, January 2014
**     Version:             rev. 2.9, 2016-03-21
**     Build:               b171205
**
**     Abstract:
**         CMSIS Peripheral Access Layer for MK64F12
**
**     The Clear BSD License
**     Copyright 1997-2016 Freescale Semiconductor, Inc.
**     Copyright 2016-2017 NXP
**     All rights reserved.
**
**     Redistribution and use in source and binary forms, with or without
**     modification, are permitted (subject to the limitations in the
**     disclaimer below) provided that the following conditions are met:
**
**     * Redistributions of source code must retain the above copyright
**       notice, this list of conditions and the following disclaimer.
**
**     * Redistributions in binary form must reproduce the above copyright
**       notice, this list of conditions and the following disclaimer in the
**       documentation and/or other materials provided with the distribution.
**
**     * Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from
**       this software without specific prior written permission.
**
**     NO EXPRESS OR IMPLIED LICENSES TO ANY PARTY'S PATENT RIGHTS ARE
**     GRANTED BY THIS LICENSE. THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT
**     HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
**     WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
**     MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
**     LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
**     CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
**     SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
**     BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
**     WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
**     OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
**     IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**     http:                 www.nxp.com
**     mail:                 support@nxp.com
**
**     Revisions:
**     - rev. 1.0 (2013-08-12)
**         Initial version.
**     - rev. 2.0 (2013-10-29)
**         Register accessor macros added to the memory map.
**         Symbols for Processor Expert memory map compatibility added to the memory map.
**         Startup file for gcc has been updated according to CMSIS 3.2.
**         System initialization updated.
**         MCG - registers updated.
**         PORTA, PORTB, PORTC, PORTE - registers for digital filter removed.
**     - rev. 2.1 (2013-10-30)
**         Definition of BITBAND macros updated to support peripherals with 32-bit acces disabled.
**     - rev. 2.2 (2013-12-09)
**         DMA - EARS register removed.
**         AIPS0, AIPS1 - MPRA register updated.
**     - rev. 2.3 (2014-01-24)
**         Update according to reference manual rev. 2
**         ENET, MCG, MCM, SIM, USB - registers updated
**     - rev. 2.4 (2014-02-10)
**         The declaration of clock configurations has been moved to separate header file system_MK64F12.h
**         Update of SystemInit() and SystemCoreClockUpdate() functions.
**     - rev. 2.5 (2014-02-10)
**         The declaration of clock configurations has been moved to separate header file system_MK64F12.h
**         Update of SystemInit() and SystemCoreClockUpdate() functions.
**         Module access macro module_BASES replaced by module_BASE_PTRS.
**     - rev. 2.6 (2014-08-28)
**         Update of system files - default clock configuration changed.
**         Update of startup files - possibility to override DefaultISR added.
**     - rev. 2.7 (2014-10-14)
**         Interrupt INT_LPTimer renamed to INT_LPTMR0, interrupt INT_Watchdog renamed to INT_WDOG_EWM.
**     - rev. 2.8 (2015-02-19)
**         Renamed interrupt vector LLW to LLWU.
**     - rev. 2.9 (2016-03-21)
**         Added MK64FN1M0CAJ12 part.
**         GPIO - renamed port instances: PTx -> GPIOx.
**
** ###################################################################
*/

#ifndef SOURCES_SYSMPU_H_
#define SOURCES_SYSMPU_H_


#ifndef __IO
  #define __IO volatile
#endif

#ifndef __I
  #define __I
#endif


/* ----------------------------------------------------------------------------
   -- SYSMPU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSMPU_Peripheral_Access_Layer SYSMPU Peripheral Access Layer
 * @{
 */

/** SYSMPU - Register Layout Typedef */
typedef struct {
  __IO uint32_t CESR;                              /**< Control/Error Status Register, offset: 0x0 */
       uint8_t RESERVED_0[12];
  struct {                                         /* offset: 0x10, array step: 0x8 */
    __I  uint32_t EAR;                               /**< Error Address Register, slave port n, array offset: 0x10, array step: 0x8 */
    __I  uint32_t EDR;                               /**< Error Detail Register, slave port n, array offset: 0x14, array step: 0x8 */
  } SP[5];
       uint8_t RESERVED_1[968];
  __IO uint32_t WORD[12][4];                       /**< Region Descriptor n, Word 0..Region Descriptor n, Word 3, array offset: 0x400, array step: index*0x10, index2*0x4 */
       uint8_t RESERVED_2[832];
  __IO uint32_t RGDAAC[12];                        /**< Region Descriptor Alternate Access Control n, array offset: 0x800, array step: 0x4 */
} SYSMPU_Type;

/* ----------------------------------------------------------------------------
   -- SYSMPU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SYSMPU_Register_Masks SYSMPU Register Masks
 * @{
 */

/*! @name CESR - Control/Error Status Register */
#define SYSMPU_CESR_VLD_MASK                     (0x1U)
#define SYSMPU_CESR_VLD_SHIFT                    (0U)
#define SYSMPU_CESR_VLD(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_VLD_SHIFT)) & SYSMPU_CESR_VLD_MASK)
#define SYSMPU_CESR_NRGD_MASK                    (0xF00U)
#define SYSMPU_CESR_NRGD_SHIFT                   (8U)
#define SYSMPU_CESR_NRGD(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_NRGD_SHIFT)) & SYSMPU_CESR_NRGD_MASK)
#define SYSMPU_CESR_NSP_MASK                     (0xF000U)
#define SYSMPU_CESR_NSP_SHIFT                    (12U)
#define SYSMPU_CESR_NSP(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_NSP_SHIFT)) & SYSMPU_CESR_NSP_MASK)
#define SYSMPU_CESR_HRL_MASK                     (0xF0000U)
#define SYSMPU_CESR_HRL_SHIFT                    (16U)
#define SYSMPU_CESR_HRL(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_HRL_SHIFT)) & SYSMPU_CESR_HRL_MASK)
#define SYSMPU_CESR_SPERR_MASK                   (0xF8000000U)
#define SYSMPU_CESR_SPERR_SHIFT                  (27U)
#define SYSMPU_CESR_SPERR(x)                     (((uint32_t)(((uint32_t)(x)) << SYSMPU_CESR_SPERR_SHIFT)) & SYSMPU_CESR_SPERR_MASK)

/*! @name EAR - Error Address Register, slave port n */
#define SYSMPU_EAR_EADDR_MASK                    (0xFFFFFFFFU)
#define SYSMPU_EAR_EADDR_SHIFT                   (0U)
#define SYSMPU_EAR_EADDR(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_EAR_EADDR_SHIFT)) & SYSMPU_EAR_EADDR_MASK)

/* The count of SYSMPU_EAR */
#define SYSMPU_EAR_COUNT                         (5U)

/*! @name EDR - Error Detail Register, slave port n */
#define SYSMPU_EDR_ERW_MASK                      (0x1U)
#define SYSMPU_EDR_ERW_SHIFT                     (0U)
#define SYSMPU_EDR_ERW(x)                        (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_ERW_SHIFT)) & SYSMPU_EDR_ERW_MASK)
#define SYSMPU_EDR_EATTR_MASK                    (0xEU)
#define SYSMPU_EDR_EATTR_SHIFT                   (1U)
#define SYSMPU_EDR_EATTR(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_EATTR_SHIFT)) & SYSMPU_EDR_EATTR_MASK)
#define SYSMPU_EDR_EMN_MASK                      (0xF0U)
#define SYSMPU_EDR_EMN_SHIFT                     (4U)
#define SYSMPU_EDR_EMN(x)                        (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_EMN_SHIFT)) & SYSMPU_EDR_EMN_MASK)
#define SYSMPU_EDR_EPID_MASK                     (0xFF00U)
#define SYSMPU_EDR_EPID_SHIFT                    (8U)
#define SYSMPU_EDR_EPID(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_EPID_SHIFT)) & SYSMPU_EDR_EPID_MASK)
#define SYSMPU_EDR_EACD_MASK                     (0xFFFF0000U)
#define SYSMPU_EDR_EACD_SHIFT                    (16U)
#define SYSMPU_EDR_EACD(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_EDR_EACD_SHIFT)) & SYSMPU_EDR_EACD_MASK)

/* The count of SYSMPU_EDR */
#define SYSMPU_EDR_COUNT                         (5U)

/*! @name WORD - Region Descriptor n, Word 0..Region Descriptor n, Word 3 */
#define SYSMPU_WORD_VLD_MASK                     (0x1U)
#define SYSMPU_WORD_VLD_SHIFT                    (0U)
#define SYSMPU_WORD_VLD(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_VLD_SHIFT)) & SYSMPU_WORD_VLD_MASK)
#define SYSMPU_WORD_M0UM_MASK                    (0x7U)
#define SYSMPU_WORD_M0UM_SHIFT                   (0U)
#define SYSMPU_WORD_M0UM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M0UM_SHIFT)) & SYSMPU_WORD_M0UM_MASK)
#define SYSMPU_WORD_M0SM_MASK                    (0x18U)
#define SYSMPU_WORD_M0SM_SHIFT                   (3U)
#define SYSMPU_WORD_M0SM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M0SM_SHIFT)) & SYSMPU_WORD_M0SM_MASK)
#define SYSMPU_WORD_M0PE_MASK                    (0x20U)
#define SYSMPU_WORD_M0PE_SHIFT                   (5U)
#define SYSMPU_WORD_M0PE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M0PE_SHIFT)) & SYSMPU_WORD_M0PE_MASK)
#define SYSMPU_WORD_ENDADDR_MASK                 (0xFFFFFFE0U)
#define SYSMPU_WORD_ENDADDR_SHIFT                (5U)
#define SYSMPU_WORD_ENDADDR(x)                   (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_ENDADDR_SHIFT)) & SYSMPU_WORD_ENDADDR_MASK)
#define SYSMPU_WORD_SRTADDR_MASK                 (0xFFFFFFE0U)
#define SYSMPU_WORD_SRTADDR_SHIFT                (5U)
#define SYSMPU_WORD_SRTADDR(x)                   (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_SRTADDR_SHIFT)) & SYSMPU_WORD_SRTADDR_MASK)
#define SYSMPU_WORD_M1UM_MASK                    (0x1C0U)
#define SYSMPU_WORD_M1UM_SHIFT                   (6U)
#define SYSMPU_WORD_M1UM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M1UM_SHIFT)) & SYSMPU_WORD_M1UM_MASK)
#define SYSMPU_WORD_M1SM_MASK                    (0x600U)
#define SYSMPU_WORD_M1SM_SHIFT                   (9U)
#define SYSMPU_WORD_M1SM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M1SM_SHIFT)) & SYSMPU_WORD_M1SM_MASK)
#define SYSMPU_WORD_M1PE_MASK                    (0x800U)
#define SYSMPU_WORD_M1PE_SHIFT                   (11U)
#define SYSMPU_WORD_M1PE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M1PE_SHIFT)) & SYSMPU_WORD_M1PE_MASK)
#define SYSMPU_WORD_M2UM_MASK                    (0x7000U)
#define SYSMPU_WORD_M2UM_SHIFT                   (12U)
#define SYSMPU_WORD_M2UM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M2UM_SHIFT)) & SYSMPU_WORD_M2UM_MASK)
#define SYSMPU_WORD_M2SM_MASK                    (0x18000U)
#define SYSMPU_WORD_M2SM_SHIFT                   (15U)
#define SYSMPU_WORD_M2SM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M2SM_SHIFT)) & SYSMPU_WORD_M2SM_MASK)
#define SYSMPU_WORD_PIDMASK_MASK                 (0xFF0000U)
#define SYSMPU_WORD_PIDMASK_SHIFT                (16U)
#define SYSMPU_WORD_PIDMASK(x)                   (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_PIDMASK_SHIFT)) & SYSMPU_WORD_PIDMASK_MASK)
#define SYSMPU_WORD_M2PE_MASK                    (0x20000U)
#define SYSMPU_WORD_M2PE_SHIFT                   (17U)
#define SYSMPU_WORD_M2PE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M2PE_SHIFT)) & SYSMPU_WORD_M2PE_MASK)
#define SYSMPU_WORD_M3UM_MASK                    (0x1C0000U)
#define SYSMPU_WORD_M3UM_SHIFT                   (18U)
#define SYSMPU_WORD_M3UM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M3UM_SHIFT)) & SYSMPU_WORD_M3UM_MASK)
#define SYSMPU_WORD_M3SM_MASK                    (0x600000U)
#define SYSMPU_WORD_M3SM_SHIFT                   (21U)
#define SYSMPU_WORD_M3SM(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M3SM_SHIFT)) & SYSMPU_WORD_M3SM_MASK)
#define SYSMPU_WORD_M3PE_MASK                    (0x800000U)
#define SYSMPU_WORD_M3PE_SHIFT                   (23U)
#define SYSMPU_WORD_M3PE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M3PE_SHIFT)) & SYSMPU_WORD_M3PE_MASK)
#define SYSMPU_WORD_PID_MASK                     (0xFF000000U)
#define SYSMPU_WORD_PID_SHIFT                    (24U)
#define SYSMPU_WORD_PID(x)                       (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_PID_SHIFT)) & SYSMPU_WORD_PID_MASK)
#define SYSMPU_WORD_M4WE_MASK                    (0x1000000U)
#define SYSMPU_WORD_M4WE_SHIFT                   (24U)
#define SYSMPU_WORD_M4WE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M4WE_SHIFT)) & SYSMPU_WORD_M4WE_MASK)
#define SYSMPU_WORD_M4RE_MASK                    (0x2000000U)
#define SYSMPU_WORD_M4RE_SHIFT                   (25U)
#define SYSMPU_WORD_M4RE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M4RE_SHIFT)) & SYSMPU_WORD_M4RE_MASK)
#define SYSMPU_WORD_M5WE_MASK                    (0x4000000U)
#define SYSMPU_WORD_M5WE_SHIFT                   (26U)
#define SYSMPU_WORD_M5WE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M5WE_SHIFT)) & SYSMPU_WORD_M5WE_MASK)
#define SYSMPU_WORD_M5RE_MASK                    (0x8000000U)
#define SYSMPU_WORD_M5RE_SHIFT                   (27U)
#define SYSMPU_WORD_M5RE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M5RE_SHIFT)) & SYSMPU_WORD_M5RE_MASK)
#define SYSMPU_WORD_M6WE_MASK                    (0x10000000U)
#define SYSMPU_WORD_M6WE_SHIFT                   (28U)
#define SYSMPU_WORD_M6WE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M6WE_SHIFT)) & SYSMPU_WORD_M6WE_MASK)
#define SYSMPU_WORD_M6RE_MASK                    (0x20000000U)
#define SYSMPU_WORD_M6RE_SHIFT                   (29U)
#define SYSMPU_WORD_M6RE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M6RE_SHIFT)) & SYSMPU_WORD_M6RE_MASK)
#define SYSMPU_WORD_M7WE_MASK                    (0x40000000U)
#define SYSMPU_WORD_M7WE_SHIFT                   (30U)
#define SYSMPU_WORD_M7WE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M7WE_SHIFT)) & SYSMPU_WORD_M7WE_MASK)
#define SYSMPU_WORD_M7RE_MASK                    (0x80000000U)
#define SYSMPU_WORD_M7RE_SHIFT                   (31U)
#define SYSMPU_WORD_M7RE(x)                      (((uint32_t)(((uint32_t)(x)) << SYSMPU_WORD_M7RE_SHIFT)) & SYSMPU_WORD_M7RE_MASK)

/* The count of SYSMPU_WORD */
#define SYSMPU_WORD_COUNT                        (12U)

/* The count of SYSMPU_WORD */
#define SYSMPU_WORD_COUNT2                       (4U)

/*! @name RGDAAC - Region Descriptor Alternate Access Control n */
#define SYSMPU_RGDAAC_M0UM_MASK                  (0x7U)
#define SYSMPU_RGDAAC_M0UM_SHIFT                 (0U)
#define SYSMPU_RGDAAC_M0UM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M0UM_SHIFT)) & SYSMPU_RGDAAC_M0UM_MASK)
#define SYSMPU_RGDAAC_M0SM_MASK                  (0x18U)
#define SYSMPU_RGDAAC_M0SM_SHIFT                 (3U)
#define SYSMPU_RGDAAC_M0SM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M0SM_SHIFT)) & SYSMPU_RGDAAC_M0SM_MASK)
#define SYSMPU_RGDAAC_M0PE_MASK                  (0x20U)
#define SYSMPU_RGDAAC_M0PE_SHIFT                 (5U)
#define SYSMPU_RGDAAC_M0PE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M0PE_SHIFT)) & SYSMPU_RGDAAC_M0PE_MASK)
#define SYSMPU_RGDAAC_M1UM_MASK                  (0x1C0U)
#define SYSMPU_RGDAAC_M1UM_SHIFT                 (6U)
#define SYSMPU_RGDAAC_M1UM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M1UM_SHIFT)) & SYSMPU_RGDAAC_M1UM_MASK)
#define SYSMPU_RGDAAC_M1SM_MASK                  (0x600U)
#define SYSMPU_RGDAAC_M1SM_SHIFT                 (9U)
#define SYSMPU_RGDAAC_M1SM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M1SM_SHIFT)) & SYSMPU_RGDAAC_M1SM_MASK)
#define SYSMPU_RGDAAC_M1PE_MASK                  (0x800U)
#define SYSMPU_RGDAAC_M1PE_SHIFT                 (11U)
#define SYSMPU_RGDAAC_M1PE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M1PE_SHIFT)) & SYSMPU_RGDAAC_M1PE_MASK)
#define SYSMPU_RGDAAC_M2UM_MASK                  (0x7000U)
#define SYSMPU_RGDAAC_M2UM_SHIFT                 (12U)
#define SYSMPU_RGDAAC_M2UM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M2UM_SHIFT)) & SYSMPU_RGDAAC_M2UM_MASK)
#define SYSMPU_RGDAAC_M2SM_MASK                  (0x18000U)
#define SYSMPU_RGDAAC_M2SM_SHIFT                 (15U)
#define SYSMPU_RGDAAC_M2SM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M2SM_SHIFT)) & SYSMPU_RGDAAC_M2SM_MASK)
#define SYSMPU_RGDAAC_M2PE_MASK                  (0x20000U)
#define SYSMPU_RGDAAC_M2PE_SHIFT                 (17U)
#define SYSMPU_RGDAAC_M2PE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M2PE_SHIFT)) & SYSMPU_RGDAAC_M2PE_MASK)
#define SYSMPU_RGDAAC_M3UM_MASK                  (0x1C0000U)
#define SYSMPU_RGDAAC_M3UM_SHIFT                 (18U)
#define SYSMPU_RGDAAC_M3UM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M3UM_SHIFT)) & SYSMPU_RGDAAC_M3UM_MASK)
#define SYSMPU_RGDAAC_M3SM_MASK                  (0x600000U)
#define SYSMPU_RGDAAC_M3SM_SHIFT                 (21U)
#define SYSMPU_RGDAAC_M3SM(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M3SM_SHIFT)) & SYSMPU_RGDAAC_M3SM_MASK)
#define SYSMPU_RGDAAC_M3PE_MASK                  (0x800000U)
#define SYSMPU_RGDAAC_M3PE_SHIFT                 (23U)
#define SYSMPU_RGDAAC_M3PE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M3PE_SHIFT)) & SYSMPU_RGDAAC_M3PE_MASK)
#define SYSMPU_RGDAAC_M4WE_MASK                  (0x1000000U)
#define SYSMPU_RGDAAC_M4WE_SHIFT                 (24U)
#define SYSMPU_RGDAAC_M4WE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M4WE_SHIFT)) & SYSMPU_RGDAAC_M4WE_MASK)
#define SYSMPU_RGDAAC_M4RE_MASK                  (0x2000000U)
#define SYSMPU_RGDAAC_M4RE_SHIFT                 (25U)
#define SYSMPU_RGDAAC_M4RE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M4RE_SHIFT)) & SYSMPU_RGDAAC_M4RE_MASK)
#define SYSMPU_RGDAAC_M5WE_MASK                  (0x4000000U)
#define SYSMPU_RGDAAC_M5WE_SHIFT                 (26U)
#define SYSMPU_RGDAAC_M5WE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M5WE_SHIFT)) & SYSMPU_RGDAAC_M5WE_MASK)
#define SYSMPU_RGDAAC_M5RE_MASK                  (0x8000000U)
#define SYSMPU_RGDAAC_M5RE_SHIFT                 (27U)
#define SYSMPU_RGDAAC_M5RE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M5RE_SHIFT)) & SYSMPU_RGDAAC_M5RE_MASK)
#define SYSMPU_RGDAAC_M6WE_MASK                  (0x10000000U)
#define SYSMPU_RGDAAC_M6WE_SHIFT                 (28U)
#define SYSMPU_RGDAAC_M6WE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M6WE_SHIFT)) & SYSMPU_RGDAAC_M6WE_MASK)
#define SYSMPU_RGDAAC_M6RE_MASK                  (0x20000000U)
#define SYSMPU_RGDAAC_M6RE_SHIFT                 (29U)
#define SYSMPU_RGDAAC_M6RE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M6RE_SHIFT)) & SYSMPU_RGDAAC_M6RE_MASK)
#define SYSMPU_RGDAAC_M7WE_MASK                  (0x40000000U)
#define SYSMPU_RGDAAC_M7WE_SHIFT                 (30U)
#define SYSMPU_RGDAAC_M7WE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M7WE_SHIFT)) & SYSMPU_RGDAAC_M7WE_MASK)
#define SYSMPU_RGDAAC_M7RE_MASK                  (0x80000000U)
#define SYSMPU_RGDAAC_M7RE_SHIFT                 (31U)
#define SYSMPU_RGDAAC_M7RE(x)                    (((uint32_t)(((uint32_t)(x)) << SYSMPU_RGDAAC_M7RE_SHIFT)) & SYSMPU_RGDAAC_M7RE_MASK)

/* The count of SYSMPU_RGDAAC */
#define SYSMPU_RGDAAC_COUNT                      (12U)


/*!
 * @}
 */ /* end of group SYSMPU_Register_Masks */


/* SYSMPU - Peripheral instance base addresses */
/** Peripheral SYSMPU base address */
#define SYSMPU_BASE                              (0x4000D000u)
/** Peripheral SYSMPU base pointer */
#define SYSMPU                                   ((SYSMPU_Type *)SYSMPU_BASE)
/** Array initializer of SYSMPU peripheral base addresses */
#define SYSMPU_BASE_ADDRS                        { SYSMPU_BASE }
/** Array initializer of SYSMPU peripheral base pointers */
#define SYSMPU_BASE_PTRS                         { SYSMPU }

/*!
 * @}
 */ /* end of group SYSMPU_Peripheral_Access_Layer */



#endif /* SOURCES_SYSMPU_H_ */
