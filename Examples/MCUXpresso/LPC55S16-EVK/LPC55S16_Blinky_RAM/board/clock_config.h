/***********************************************************************************************************************
 * This file was generated by the MCUXpresso Config Tools. Any manual edits made to this file
 * will be overwritten if the respective MCUXpresso Config Tools is used to update this file.
 **********************************************************************************************************************/

#ifndef _CLOCK_CONFIG_H_
#define _CLOCK_CONFIG_H_

#include "fsl_common.h"

/*******************************************************************************
 * Definitions
 ******************************************************************************/
#define BOARD_XTAL0_CLK_HZ                         16000000U  /*!< Board xtal frequency in Hz */
#define BOARD_XTAL32K_CLK_HZ                          32768U  /*!< Board xtal32K frequency in Hz */

/*******************************************************************************
 ************************ BOARD_InitBootClocks function ************************
 ******************************************************************************/

#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes default configuration of clocks.
 *
 */
void BOARD_InitBootClocks(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ******************** Configuration BOARD_BootClockFRO12M **********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockFRO12M configuration
 ******************************************************************************/
#define BOARD_BOOTCLOCKFRO12M_CORE_CLOCK           12000000U  /*!< Core clock frequency: 12000000Hz */


/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKFRO12M_ASYNCADC_CLOCK          0UL            /* Clock consumers of ASYNCADC_clock output : ADC0 */
#define BOARD_BOOTCLOCKFRO12M_CAN_CLOCK               0UL            /* Clock consumers of CAN_clock output : CAN0 */
#define BOARD_BOOTCLOCKFRO12M_CLKOUT_CLOCK            0UL            /* Clock consumers of CLKOUT_clock output : N/A */
#define BOARD_BOOTCLOCKFRO12M_CTIMER0_CLOCK           0UL            /* Clock consumers of CTIMER0_clock output : CTIMER0 */
#define BOARD_BOOTCLOCKFRO12M_CTIMER1_CLOCK           0UL            /* Clock consumers of CTIMER1_clock output : CTIMER1 */
#define BOARD_BOOTCLOCKFRO12M_CTIMER2_CLOCK           0UL            /* Clock consumers of CTIMER2_clock output : CTIMER2 */
#define BOARD_BOOTCLOCKFRO12M_CTIMER3_CLOCK           0UL            /* Clock consumers of CTIMER3_clock output : CTIMER3 */
#define BOARD_BOOTCLOCKFRO12M_CTIMER4_CLOCK           0UL            /* Clock consumers of CTIMER4_clock output : CTIMER4 */
#define BOARD_BOOTCLOCKFRO12M_FRO_12MHZ_CLOCK         12000000UL     /* Clock consumers of FRO_12MHz_clock output : ANACTRL */
#define BOARD_BOOTCLOCKFRO12M_FRO_1MHZ_CLOCK          0UL            /* Clock consumers of FRO_1MHz_clock output : N/A */
#define BOARD_BOOTCLOCKFRO12M_FXCOM0_CLOCK            0UL            /* Clock consumers of FXCOM0_clock output : FLEXCOMM0 */
#define BOARD_BOOTCLOCKFRO12M_FXCOM1_CLOCK            0UL            /* Clock consumers of FXCOM1_clock output : FLEXCOMM1 */
#define BOARD_BOOTCLOCKFRO12M_FXCOM2_CLOCK            0UL            /* Clock consumers of FXCOM2_clock output : FLEXCOMM2 */
#define BOARD_BOOTCLOCKFRO12M_FXCOM3_CLOCK            0UL            /* Clock consumers of FXCOM3_clock output : FLEXCOMM3 */
#define BOARD_BOOTCLOCKFRO12M_FXCOM4_CLOCK            0UL            /* Clock consumers of FXCOM4_clock output : FLEXCOMM4 */
#define BOARD_BOOTCLOCKFRO12M_FXCOM5_CLOCK            0UL            /* Clock consumers of FXCOM5_clock output : FLEXCOMM5 */
#define BOARD_BOOTCLOCKFRO12M_FXCOM6_CLOCK            0UL            /* Clock consumers of FXCOM6_clock output : FLEXCOMM6 */
#define BOARD_BOOTCLOCKFRO12M_FXCOM7_CLOCK            0UL            /* Clock consumers of FXCOM7_clock output : FLEXCOMM7 */
#define BOARD_BOOTCLOCKFRO12M_HSLSPI_CLOCK            0UL            /* Clock consumers of HSLSPI_clock output : FLEXCOMM8 */
#define BOARD_BOOTCLOCKFRO12M_HSUSB1_32K_CLOCK        0UL            /* Clock consumers of HSUSB1_32K_clock output : USBPHY */
#define BOARD_BOOTCLOCKFRO12M_MCLK_CLOCK              0UL            /* Clock consumers of MCLK_clock output : N/A */
#define BOARD_BOOTCLOCKFRO12M_OSC32KHZ_CLOCK          0UL            /* Clock consumers of OSC32KHZ_clock output : FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, USBHSD, USBHSH */
#define BOARD_BOOTCLOCKFRO12M_OSTIMER_CLOCK           0UL            /* Clock consumers of OSTIMER_clock output : OSTIMER */
#define BOARD_BOOTCLOCKFRO12M_PLUCLKIN_CLOCK          0UL            /* Clock consumers of PLUCLKIN_clock output : PLU */
#define BOARD_BOOTCLOCKFRO12M_PLU_GLITCH_12MHZ_CLOCK  0UL            /* Clock consumers of PLU_GLITCH_12MHz_clock output : PLU */
#define BOARD_BOOTCLOCKFRO12M_PLU_GLITCH_1MHZ_CLOCK   0UL            /* Clock consumers of PLU_GLITCH_1MHz_clock output : PLU */
#define BOARD_BOOTCLOCKFRO12M_RTC1HZ_CLOCK            0UL            /* Clock consumers of RTC1HZ_clock output : N/A */
#define BOARD_BOOTCLOCKFRO12M_RTC1KHZ_CLOCK           0UL            /* Clock consumers of RTC1KHZ_clock output : N/A */
#define BOARD_BOOTCLOCKFRO12M_SCT_CLOCK               0UL            /* Clock consumers of SCT_clock output : SCT0 */
#define BOARD_BOOTCLOCKFRO12M_SYSTICK0_CLOCK          0UL            /* Clock consumers of SYSTICK0_clock output : N/A */
#define BOARD_BOOTCLOCKFRO12M_SYSTEM_CLOCK            12000000UL     /* Clock consumers of System_clock output : ADC0, ANACTRL, CAN0, CASPER, CRC_ENGINE, CTIMER0, CTIMER1, CTIMER2, CTIMER3, CTIMER4, DMA0, DMA1, FLASH, FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, GINT0, GINT1, GPIO, INPUTMUX, IOCON, MRT0, OSTIMER, PINT, PLU, PUF, SCT0, SECGPIO, SECPINT, SWD, SYSCTL, USB0, USBFSH, USBHSD, USBHSH, USBPHY, UTICK0, WWDT */
#define BOARD_BOOTCLOCKFRO12M_TRACE_CLOCK             0UL            /* Clock consumers of TRACE_clock output : SWD */
#define BOARD_BOOTCLOCKFRO12M_USB0_CLOCK              0UL            /* Clock consumers of USB0_clock output : USB0, USBFSH */
#define BOARD_BOOTCLOCKFRO12M_USB1_PHY_CLOCK          0UL            /* Clock consumers of USB1_PHY_clock output : USBHSD, USBHSH, USBPHY */
#define BOARD_BOOTCLOCKFRO12M_UTICK_CLOCK             0UL            /* Clock consumers of UTICK_clock output : UTICK0 */
#define BOARD_BOOTCLOCKFRO12M_WDT_CLOCK               0UL            /* Clock consumers of WDT_clock output : WWDT */

/*******************************************************************************
 * API for BOARD_BootClockFRO12M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockFRO12M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ******************* Configuration BOARD_BootClockFROHF96M *********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockFROHF96M configuration
 ******************************************************************************/
#define BOARD_BOOTCLOCKFROHF96M_CORE_CLOCK         96000000U  /*!< Core clock frequency: 96000000Hz */


/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKFROHF96M_ASYNCADC_CLOCK        0UL            /* Clock consumers of ASYNCADC_clock output : ADC0 */
#define BOARD_BOOTCLOCKFROHF96M_CAN_CLOCK             0UL            /* Clock consumers of CAN_clock output : CAN0 */
#define BOARD_BOOTCLOCKFROHF96M_CLKOUT_CLOCK          0UL            /* Clock consumers of CLKOUT_clock output : N/A */
#define BOARD_BOOTCLOCKFROHF96M_CTIMER0_CLOCK         0UL            /* Clock consumers of CTIMER0_clock output : CTIMER0 */
#define BOARD_BOOTCLOCKFROHF96M_CTIMER1_CLOCK         0UL            /* Clock consumers of CTIMER1_clock output : CTIMER1 */
#define BOARD_BOOTCLOCKFROHF96M_CTIMER2_CLOCK         0UL            /* Clock consumers of CTIMER2_clock output : CTIMER2 */
#define BOARD_BOOTCLOCKFROHF96M_CTIMER3_CLOCK         0UL            /* Clock consumers of CTIMER3_clock output : CTIMER3 */
#define BOARD_BOOTCLOCKFROHF96M_CTIMER4_CLOCK         0UL            /* Clock consumers of CTIMER4_clock output : CTIMER4 */
#define BOARD_BOOTCLOCKFROHF96M_FRO_12MHZ_CLOCK       12000000UL     /* Clock consumers of FRO_12MHz_clock output : ANACTRL */
#define BOARD_BOOTCLOCKFROHF96M_FRO_1MHZ_CLOCK        0UL            /* Clock consumers of FRO_1MHz_clock output : N/A */
#define BOARD_BOOTCLOCKFROHF96M_FXCOM0_CLOCK          0UL            /* Clock consumers of FXCOM0_clock output : FLEXCOMM0 */
#define BOARD_BOOTCLOCKFROHF96M_FXCOM1_CLOCK          0UL            /* Clock consumers of FXCOM1_clock output : FLEXCOMM1 */
#define BOARD_BOOTCLOCKFROHF96M_FXCOM2_CLOCK          0UL            /* Clock consumers of FXCOM2_clock output : FLEXCOMM2 */
#define BOARD_BOOTCLOCKFROHF96M_FXCOM3_CLOCK          0UL            /* Clock consumers of FXCOM3_clock output : FLEXCOMM3 */
#define BOARD_BOOTCLOCKFROHF96M_FXCOM4_CLOCK          0UL            /* Clock consumers of FXCOM4_clock output : FLEXCOMM4 */
#define BOARD_BOOTCLOCKFROHF96M_FXCOM5_CLOCK          0UL            /* Clock consumers of FXCOM5_clock output : FLEXCOMM5 */
#define BOARD_BOOTCLOCKFROHF96M_FXCOM6_CLOCK          0UL            /* Clock consumers of FXCOM6_clock output : FLEXCOMM6 */
#define BOARD_BOOTCLOCKFROHF96M_FXCOM7_CLOCK          0UL            /* Clock consumers of FXCOM7_clock output : FLEXCOMM7 */
#define BOARD_BOOTCLOCKFROHF96M_HSLSPI_CLOCK          0UL            /* Clock consumers of HSLSPI_clock output : FLEXCOMM8 */
#define BOARD_BOOTCLOCKFROHF96M_HSUSB1_32K_CLOCK      0UL            /* Clock consumers of HSUSB1_32K_clock output : USBPHY */
#define BOARD_BOOTCLOCKFROHF96M_MCLK_CLOCK            0UL            /* Clock consumers of MCLK_clock output : N/A */
#define BOARD_BOOTCLOCKFROHF96M_OSC32KHZ_CLOCK        0UL            /* Clock consumers of OSC32KHZ_clock output : FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, USBHSD, USBHSH */
#define BOARD_BOOTCLOCKFROHF96M_OSTIMER_CLOCK         0UL            /* Clock consumers of OSTIMER_clock output : OSTIMER */
#define BOARD_BOOTCLOCKFROHF96M_PLUCLKIN_CLOCK        0UL            /* Clock consumers of PLUCLKIN_clock output : PLU */
#define BOARD_BOOTCLOCKFROHF96M_PLU_GLITCH_12MHZ_CLOCK 0UL           /* Clock consumers of PLU_GLITCH_12MHz_clock output : PLU */
#define BOARD_BOOTCLOCKFROHF96M_PLU_GLITCH_1MHZ_CLOCK 0UL            /* Clock consumers of PLU_GLITCH_1MHz_clock output : PLU */
#define BOARD_BOOTCLOCKFROHF96M_RTC1HZ_CLOCK          0UL            /* Clock consumers of RTC1HZ_clock output : N/A */
#define BOARD_BOOTCLOCKFROHF96M_RTC1KHZ_CLOCK         0UL            /* Clock consumers of RTC1KHZ_clock output : N/A */
#define BOARD_BOOTCLOCKFROHF96M_SCT_CLOCK             0UL            /* Clock consumers of SCT_clock output : SCT0 */
#define BOARD_BOOTCLOCKFROHF96M_SYSTICK0_CLOCK        0UL            /* Clock consumers of SYSTICK0_clock output : N/A */
#define BOARD_BOOTCLOCKFROHF96M_SYSTEM_CLOCK          96000000UL     /* Clock consumers of System_clock output : ADC0, ANACTRL, CAN0, CASPER, CRC_ENGINE, CTIMER0, CTIMER1, CTIMER2, CTIMER3, CTIMER4, DMA0, DMA1, FLASH, FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, GINT0, GINT1, GPIO, INPUTMUX, IOCON, MRT0, OSTIMER, PINT, PLU, PUF, SCT0, SECGPIO, SECPINT, SWD, SYSCTL, USB0, USBFSH, USBHSD, USBHSH, USBPHY, UTICK0, WWDT */
#define BOARD_BOOTCLOCKFROHF96M_TRACE_CLOCK           0UL            /* Clock consumers of TRACE_clock output : SWD */
#define BOARD_BOOTCLOCKFROHF96M_USB0_CLOCK            0UL            /* Clock consumers of USB0_clock output : USB0, USBFSH */
#define BOARD_BOOTCLOCKFROHF96M_USB1_PHY_CLOCK        0UL            /* Clock consumers of USB1_PHY_clock output : USBHSD, USBHSH, USBPHY */
#define BOARD_BOOTCLOCKFROHF96M_UTICK_CLOCK           0UL            /* Clock consumers of UTICK_clock output : UTICK0 */
#define BOARD_BOOTCLOCKFROHF96M_WDT_CLOCK             0UL            /* Clock consumers of WDT_clock output : WWDT */

/*******************************************************************************
 * API for BOARD_BootClockFROHF96M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockFROHF96M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ******************** Configuration BOARD_BootClockPLL100M *********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockPLL100M configuration
 ******************************************************************************/
#define BOARD_BOOTCLOCKPLL100M_CORE_CLOCK         100000000U  /*!< Core clock frequency: 100000000Hz */


/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKPLL100M_ASYNCADC_CLOCK         0UL            /* Clock consumers of ASYNCADC_clock output : ADC0 */
#define BOARD_BOOTCLOCKPLL100M_CAN_CLOCK              0UL            /* Clock consumers of CAN_clock output : CAN0 */
#define BOARD_BOOTCLOCKPLL100M_CLKOUT_CLOCK           0UL            /* Clock consumers of CLKOUT_clock output : N/A */
#define BOARD_BOOTCLOCKPLL100M_CTIMER0_CLOCK          0UL            /* Clock consumers of CTIMER0_clock output : CTIMER0 */
#define BOARD_BOOTCLOCKPLL100M_CTIMER1_CLOCK          0UL            /* Clock consumers of CTIMER1_clock output : CTIMER1 */
#define BOARD_BOOTCLOCKPLL100M_CTIMER2_CLOCK          0UL            /* Clock consumers of CTIMER2_clock output : CTIMER2 */
#define BOARD_BOOTCLOCKPLL100M_CTIMER3_CLOCK          0UL            /* Clock consumers of CTIMER3_clock output : CTIMER3 */
#define BOARD_BOOTCLOCKPLL100M_CTIMER4_CLOCK          0UL            /* Clock consumers of CTIMER4_clock output : CTIMER4 */
#define BOARD_BOOTCLOCKPLL100M_FRO_12MHZ_CLOCK        12000000UL     /* Clock consumers of FRO_12MHz_clock output : ANACTRL */
#define BOARD_BOOTCLOCKPLL100M_FRO_1MHZ_CLOCK         0UL            /* Clock consumers of FRO_1MHz_clock output : N/A */
#define BOARD_BOOTCLOCKPLL100M_FXCOM0_CLOCK           0UL            /* Clock consumers of FXCOM0_clock output : FLEXCOMM0 */
#define BOARD_BOOTCLOCKPLL100M_FXCOM1_CLOCK           0UL            /* Clock consumers of FXCOM1_clock output : FLEXCOMM1 */
#define BOARD_BOOTCLOCKPLL100M_FXCOM2_CLOCK           0UL            /* Clock consumers of FXCOM2_clock output : FLEXCOMM2 */
#define BOARD_BOOTCLOCKPLL100M_FXCOM3_CLOCK           0UL            /* Clock consumers of FXCOM3_clock output : FLEXCOMM3 */
#define BOARD_BOOTCLOCKPLL100M_FXCOM4_CLOCK           0UL            /* Clock consumers of FXCOM4_clock output : FLEXCOMM4 */
#define BOARD_BOOTCLOCKPLL100M_FXCOM5_CLOCK           0UL            /* Clock consumers of FXCOM5_clock output : FLEXCOMM5 */
#define BOARD_BOOTCLOCKPLL100M_FXCOM6_CLOCK           0UL            /* Clock consumers of FXCOM6_clock output : FLEXCOMM6 */
#define BOARD_BOOTCLOCKPLL100M_FXCOM7_CLOCK           0UL            /* Clock consumers of FXCOM7_clock output : FLEXCOMM7 */
#define BOARD_BOOTCLOCKPLL100M_HSLSPI_CLOCK           0UL            /* Clock consumers of HSLSPI_clock output : FLEXCOMM8 */
#define BOARD_BOOTCLOCKPLL100M_HSUSB1_32K_CLOCK       0UL            /* Clock consumers of HSUSB1_32K_clock output : USBPHY */
#define BOARD_BOOTCLOCKPLL100M_MCLK_CLOCK             0UL            /* Clock consumers of MCLK_clock output : N/A */
#define BOARD_BOOTCLOCKPLL100M_OSC32KHZ_CLOCK         0UL            /* Clock consumers of OSC32KHZ_clock output : FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, USBHSD, USBHSH */
#define BOARD_BOOTCLOCKPLL100M_OSTIMER_CLOCK          0UL            /* Clock consumers of OSTIMER_clock output : OSTIMER */
#define BOARD_BOOTCLOCKPLL100M_PLUCLKIN_CLOCK         0UL            /* Clock consumers of PLUCLKIN_clock output : PLU */
#define BOARD_BOOTCLOCKPLL100M_PLU_GLITCH_12MHZ_CLOCK 0UL            /* Clock consumers of PLU_GLITCH_12MHz_clock output : PLU */
#define BOARD_BOOTCLOCKPLL100M_PLU_GLITCH_1MHZ_CLOCK  0UL            /* Clock consumers of PLU_GLITCH_1MHz_clock output : PLU */
#define BOARD_BOOTCLOCKPLL100M_RTC1HZ_CLOCK           0UL            /* Clock consumers of RTC1HZ_clock output : N/A */
#define BOARD_BOOTCLOCKPLL100M_RTC1KHZ_CLOCK          0UL            /* Clock consumers of RTC1KHZ_clock output : N/A */
#define BOARD_BOOTCLOCKPLL100M_SCT_CLOCK              0UL            /* Clock consumers of SCT_clock output : SCT0 */
#define BOARD_BOOTCLOCKPLL100M_SYSTICK0_CLOCK         0UL            /* Clock consumers of SYSTICK0_clock output : N/A */
#define BOARD_BOOTCLOCKPLL100M_SYSTEM_CLOCK           100000000UL    /* Clock consumers of System_clock output : ADC0, ANACTRL, CAN0, CASPER, CRC_ENGINE, CTIMER0, CTIMER1, CTIMER2, CTIMER3, CTIMER4, DMA0, DMA1, FLASH, FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, GINT0, GINT1, GPIO, INPUTMUX, IOCON, MRT0, OSTIMER, PINT, PLU, PUF, SCT0, SECGPIO, SECPINT, SWD, SYSCTL, USB0, USBFSH, USBHSD, USBHSH, USBPHY, UTICK0, WWDT */
#define BOARD_BOOTCLOCKPLL100M_TRACE_CLOCK            0UL            /* Clock consumers of TRACE_clock output : SWD */
#define BOARD_BOOTCLOCKPLL100M_USB0_CLOCK             0UL            /* Clock consumers of USB0_clock output : USB0, USBFSH */
#define BOARD_BOOTCLOCKPLL100M_USB1_PHY_CLOCK         0UL            /* Clock consumers of USB1_PHY_clock output : USBHSD, USBHSH, USBPHY */
#define BOARD_BOOTCLOCKPLL100M_UTICK_CLOCK            0UL            /* Clock consumers of UTICK_clock output : UTICK0 */
#define BOARD_BOOTCLOCKPLL100M_WDT_CLOCK              0UL            /* Clock consumers of WDT_clock output : WWDT */

/*******************************************************************************
 * API for BOARD_BootClockPLL100M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockPLL100M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ******************** Configuration BOARD_BootClockPLL150M *********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockPLL150M configuration
 ******************************************************************************/
#define BOARD_BOOTCLOCKPLL150M_CORE_CLOCK         150000000U  /*!< Core clock frequency: 150000000Hz */


/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKPLL150M_ASYNCADC_CLOCK         0UL            /* Clock consumers of ASYNCADC_clock output : ADC0 */
#define BOARD_BOOTCLOCKPLL150M_CAN_CLOCK              0UL            /* Clock consumers of CAN_clock output : CAN0 */
#define BOARD_BOOTCLOCKPLL150M_CLKOUT_CLOCK           0UL            /* Clock consumers of CLKOUT_clock output : N/A */
#define BOARD_BOOTCLOCKPLL150M_CTIMER0_CLOCK          0UL            /* Clock consumers of CTIMER0_clock output : CTIMER0 */
#define BOARD_BOOTCLOCKPLL150M_CTIMER1_CLOCK          0UL            /* Clock consumers of CTIMER1_clock output : CTIMER1 */
#define BOARD_BOOTCLOCKPLL150M_CTIMER2_CLOCK          0UL            /* Clock consumers of CTIMER2_clock output : CTIMER2 */
#define BOARD_BOOTCLOCKPLL150M_CTIMER3_CLOCK          0UL            /* Clock consumers of CTIMER3_clock output : CTIMER3 */
#define BOARD_BOOTCLOCKPLL150M_CTIMER4_CLOCK          0UL            /* Clock consumers of CTIMER4_clock output : CTIMER4 */
#define BOARD_BOOTCLOCKPLL150M_FRO_12MHZ_CLOCK        12000000UL     /* Clock consumers of FRO_12MHz_clock output : ANACTRL */
#define BOARD_BOOTCLOCKPLL150M_FRO_1MHZ_CLOCK         0UL            /* Clock consumers of FRO_1MHz_clock output : N/A */
#define BOARD_BOOTCLOCKPLL150M_FXCOM0_CLOCK           0UL            /* Clock consumers of FXCOM0_clock output : FLEXCOMM0 */
#define BOARD_BOOTCLOCKPLL150M_FXCOM1_CLOCK           0UL            /* Clock consumers of FXCOM1_clock output : FLEXCOMM1 */
#define BOARD_BOOTCLOCKPLL150M_FXCOM2_CLOCK           0UL            /* Clock consumers of FXCOM2_clock output : FLEXCOMM2 */
#define BOARD_BOOTCLOCKPLL150M_FXCOM3_CLOCK           0UL            /* Clock consumers of FXCOM3_clock output : FLEXCOMM3 */
#define BOARD_BOOTCLOCKPLL150M_FXCOM4_CLOCK           0UL            /* Clock consumers of FXCOM4_clock output : FLEXCOMM4 */
#define BOARD_BOOTCLOCKPLL150M_FXCOM5_CLOCK           0UL            /* Clock consumers of FXCOM5_clock output : FLEXCOMM5 */
#define BOARD_BOOTCLOCKPLL150M_FXCOM6_CLOCK           0UL            /* Clock consumers of FXCOM6_clock output : FLEXCOMM6 */
#define BOARD_BOOTCLOCKPLL150M_FXCOM7_CLOCK           0UL            /* Clock consumers of FXCOM7_clock output : FLEXCOMM7 */
#define BOARD_BOOTCLOCKPLL150M_HSLSPI_CLOCK           0UL            /* Clock consumers of HSLSPI_clock output : FLEXCOMM8 */
#define BOARD_BOOTCLOCKPLL150M_HSUSB1_32K_CLOCK       0UL            /* Clock consumers of HSUSB1_32K_clock output : USBPHY */
#define BOARD_BOOTCLOCKPLL150M_MCLK_CLOCK             0UL            /* Clock consumers of MCLK_clock output : N/A */
#define BOARD_BOOTCLOCKPLL150M_OSC32KHZ_CLOCK         0UL            /* Clock consumers of OSC32KHZ_clock output : FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, USBHSD, USBHSH */
#define BOARD_BOOTCLOCKPLL150M_OSTIMER_CLOCK          0UL            /* Clock consumers of OSTIMER_clock output : OSTIMER */
#define BOARD_BOOTCLOCKPLL150M_PLUCLKIN_CLOCK         0UL            /* Clock consumers of PLUCLKIN_clock output : PLU */
#define BOARD_BOOTCLOCKPLL150M_PLU_GLITCH_12MHZ_CLOCK 0UL            /* Clock consumers of PLU_GLITCH_12MHz_clock output : PLU */
#define BOARD_BOOTCLOCKPLL150M_PLU_GLITCH_1MHZ_CLOCK  0UL            /* Clock consumers of PLU_GLITCH_1MHz_clock output : PLU */
#define BOARD_BOOTCLOCKPLL150M_RTC1HZ_CLOCK           0UL            /* Clock consumers of RTC1HZ_clock output : N/A */
#define BOARD_BOOTCLOCKPLL150M_RTC1KHZ_CLOCK          0UL            /* Clock consumers of RTC1KHZ_clock output : N/A */
#define BOARD_BOOTCLOCKPLL150M_SCT_CLOCK              0UL            /* Clock consumers of SCT_clock output : SCT0 */
#define BOARD_BOOTCLOCKPLL150M_SYSTICK0_CLOCK         0UL            /* Clock consumers of SYSTICK0_clock output : N/A */
#define BOARD_BOOTCLOCKPLL150M_SYSTEM_CLOCK           150000000UL    /* Clock consumers of System_clock output : ADC0, ANACTRL, CAN0, CASPER, CRC_ENGINE, CTIMER0, CTIMER1, CTIMER2, CTIMER3, CTIMER4, DMA0, DMA1, FLASH, FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, GINT0, GINT1, GPIO, INPUTMUX, IOCON, MRT0, OSTIMER, PINT, PLU, PUF, SCT0, SECGPIO, SECPINT, SWD, SYSCTL, USB0, USBFSH, USBHSD, USBHSH, USBPHY, UTICK0, WWDT */
#define BOARD_BOOTCLOCKPLL150M_TRACE_CLOCK            0UL            /* Clock consumers of TRACE_clock output : SWD */
#define BOARD_BOOTCLOCKPLL150M_USB0_CLOCK             0UL            /* Clock consumers of USB0_clock output : USB0, USBFSH */
#define BOARD_BOOTCLOCKPLL150M_USB1_PHY_CLOCK         0UL            /* Clock consumers of USB1_PHY_clock output : USBHSD, USBHSH, USBPHY */
#define BOARD_BOOTCLOCKPLL150M_UTICK_CLOCK            0UL            /* Clock consumers of UTICK_clock output : UTICK0 */
#define BOARD_BOOTCLOCKPLL150M_WDT_CLOCK              0UL            /* Clock consumers of WDT_clock output : WWDT */

/*******************************************************************************
 * API for BOARD_BootClockPLL150M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockPLL150M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

/*******************************************************************************
 ******************* Configuration BOARD_BootClockPLL1_150M ********************
 ******************************************************************************/
/*******************************************************************************
 * Definitions for BOARD_BootClockPLL1_150M configuration
 ******************************************************************************/
#define BOARD_BOOTCLOCKPLL1_150M_CORE_CLOCK       150000000U  /*!< Core clock frequency: 150000000Hz */


/* Clock outputs (values are in Hz): */
#define BOARD_BOOTCLOCKPLL1_150M_ASYNCADC_CLOCK       0UL            /* Clock consumers of ASYNCADC_clock output : ADC0 */
#define BOARD_BOOTCLOCKPLL1_150M_CAN_CLOCK            0UL            /* Clock consumers of CAN_clock output : CAN0 */
#define BOARD_BOOTCLOCKPLL1_150M_CLKOUT_CLOCK         0UL            /* Clock consumers of CLKOUT_clock output : N/A */
#define BOARD_BOOTCLOCKPLL1_150M_CTIMER0_CLOCK        0UL            /* Clock consumers of CTIMER0_clock output : CTIMER0 */
#define BOARD_BOOTCLOCKPLL1_150M_CTIMER1_CLOCK        0UL            /* Clock consumers of CTIMER1_clock output : CTIMER1 */
#define BOARD_BOOTCLOCKPLL1_150M_CTIMER2_CLOCK        0UL            /* Clock consumers of CTIMER2_clock output : CTIMER2 */
#define BOARD_BOOTCLOCKPLL1_150M_CTIMER3_CLOCK        0UL            /* Clock consumers of CTIMER3_clock output : CTIMER3 */
#define BOARD_BOOTCLOCKPLL1_150M_CTIMER4_CLOCK        0UL            /* Clock consumers of CTIMER4_clock output : CTIMER4 */
#define BOARD_BOOTCLOCKPLL1_150M_FRO_12MHZ_CLOCK      12000000UL     /* Clock consumers of FRO_12MHz_clock output : ANACTRL */
#define BOARD_BOOTCLOCKPLL1_150M_FRO_1MHZ_CLOCK       0UL            /* Clock consumers of FRO_1MHz_clock output : N/A */
#define BOARD_BOOTCLOCKPLL1_150M_FXCOM0_CLOCK         0UL            /* Clock consumers of FXCOM0_clock output : FLEXCOMM0 */
#define BOARD_BOOTCLOCKPLL1_150M_FXCOM1_CLOCK         0UL            /* Clock consumers of FXCOM1_clock output : FLEXCOMM1 */
#define BOARD_BOOTCLOCKPLL1_150M_FXCOM2_CLOCK         0UL            /* Clock consumers of FXCOM2_clock output : FLEXCOMM2 */
#define BOARD_BOOTCLOCKPLL1_150M_FXCOM3_CLOCK         0UL            /* Clock consumers of FXCOM3_clock output : FLEXCOMM3 */
#define BOARD_BOOTCLOCKPLL1_150M_FXCOM4_CLOCK         0UL            /* Clock consumers of FXCOM4_clock output : FLEXCOMM4 */
#define BOARD_BOOTCLOCKPLL1_150M_FXCOM5_CLOCK         0UL            /* Clock consumers of FXCOM5_clock output : FLEXCOMM5 */
#define BOARD_BOOTCLOCKPLL1_150M_FXCOM6_CLOCK         0UL            /* Clock consumers of FXCOM6_clock output : FLEXCOMM6 */
#define BOARD_BOOTCLOCKPLL1_150M_FXCOM7_CLOCK         0UL            /* Clock consumers of FXCOM7_clock output : FLEXCOMM7 */
#define BOARD_BOOTCLOCKPLL1_150M_HSLSPI_CLOCK         0UL            /* Clock consumers of HSLSPI_clock output : FLEXCOMM8 */
#define BOARD_BOOTCLOCKPLL1_150M_HSUSB1_32K_CLOCK     0UL            /* Clock consumers of HSUSB1_32K_clock output : USBPHY */
#define BOARD_BOOTCLOCKPLL1_150M_MCLK_CLOCK           0UL            /* Clock consumers of MCLK_clock output : N/A */
#define BOARD_BOOTCLOCKPLL1_150M_OSC32KHZ_CLOCK       0UL            /* Clock consumers of OSC32KHZ_clock output : FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, USBHSD, USBHSH */
#define BOARD_BOOTCLOCKPLL1_150M_OSTIMER_CLOCK        0UL            /* Clock consumers of OSTIMER_clock output : OSTIMER */
#define BOARD_BOOTCLOCKPLL1_150M_PLUCLKIN_CLOCK       0UL            /* Clock consumers of PLUCLKIN_clock output : PLU */
#define BOARD_BOOTCLOCKPLL1_150M_PLU_GLITCH_12MHZ_CLOCK 0UL          /* Clock consumers of PLU_GLITCH_12MHz_clock output : PLU */
#define BOARD_BOOTCLOCKPLL1_150M_PLU_GLITCH_1MHZ_CLOCK 0UL           /* Clock consumers of PLU_GLITCH_1MHz_clock output : PLU */
#define BOARD_BOOTCLOCKPLL1_150M_RTC1HZ_CLOCK         0UL            /* Clock consumers of RTC1HZ_clock output : N/A */
#define BOARD_BOOTCLOCKPLL1_150M_RTC1KHZ_CLOCK        0UL            /* Clock consumers of RTC1KHZ_clock output : N/A */
#define BOARD_BOOTCLOCKPLL1_150M_SCT_CLOCK            0UL            /* Clock consumers of SCT_clock output : SCT0 */
#define BOARD_BOOTCLOCKPLL1_150M_SYSTICK0_CLOCK       0UL            /* Clock consumers of SYSTICK0_clock output : N/A */
#define BOARD_BOOTCLOCKPLL1_150M_SYSTEM_CLOCK         150000000UL    /* Clock consumers of System_clock output : ADC0, ANACTRL, CAN0, CASPER, CRC_ENGINE, CTIMER0, CTIMER1, CTIMER2, CTIMER3, CTIMER4, DMA0, DMA1, FLASH, FLEXCOMM0, FLEXCOMM1, FLEXCOMM2, FLEXCOMM3, FLEXCOMM4, FLEXCOMM5, FLEXCOMM6, FLEXCOMM7, FLEXCOMM8, GINT0, GINT1, GPIO, INPUTMUX, IOCON, MRT0, OSTIMER, PINT, PLU, PUF, SCT0, SECGPIO, SECPINT, SWD, SYSCTL, USB0, USBFSH, USBHSD, USBHSH, USBPHY, UTICK0, WWDT */
#define BOARD_BOOTCLOCKPLL1_150M_TRACE_CLOCK          0UL            /* Clock consumers of TRACE_clock output : SWD */
#define BOARD_BOOTCLOCKPLL1_150M_USB0_CLOCK           0UL            /* Clock consumers of USB0_clock output : USB0, USBFSH */
#define BOARD_BOOTCLOCKPLL1_150M_USB1_PHY_CLOCK       0UL            /* Clock consumers of USB1_PHY_clock output : USBHSD, USBHSH, USBPHY */
#define BOARD_BOOTCLOCKPLL1_150M_UTICK_CLOCK          0UL            /* Clock consumers of UTICK_clock output : UTICK0 */
#define BOARD_BOOTCLOCKPLL1_150M_WDT_CLOCK            0UL            /* Clock consumers of WDT_clock output : WWDT */

/*******************************************************************************
 * API for BOARD_BootClockPLL1_150M configuration
 ******************************************************************************/
#if defined(__cplusplus)
extern "C" {
#endif /* __cplusplus*/

/*!
 * @brief This function executes configuration of clocks.
 *
 */
void BOARD_BootClockPLL1_150M(void);

#if defined(__cplusplus)
}
#endif /* __cplusplus*/

#endif /* _CLOCK_CONFIG_H_ */

