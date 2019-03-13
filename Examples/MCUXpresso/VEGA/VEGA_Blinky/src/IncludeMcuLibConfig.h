/*
 * IncludeMcuLibConfig.h
 */

/* this header file is included with the compiler option -include */

//#ifndef SRC_INCLUDEMCULIBCONFIG_H_
//#define SRC_INCLUDEMCULIBCONFIG_H_

#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0

#define McuLib_CONFIG_CPU_IS_ARM_CORTEX_M    (0)
#define McuLib_CONFIG_CPU_IS_RISC_V          (1)

#define McuLib_CONFIG_SDK_USE_FREERTOS       (0)

#define McuLib_CONFIG_SDK_VERSION_MAJOR   (2)
#define McuLib_CONFIG_SDK_VERSION_MINOR   (2)
#define McuLib_CONFIG_SDK_VERSION_BUILD   (0)

/* red LED */
#define McuLED1_CONFIG_IS_LOW_ACTIVE   (0)
#define LEDpin1_CONFIG_GPIO_NAME       GPIOA
#define LEDpin1_CONFIG_PORT_NAME       PORTA
#define LEDpin1_CONFIG_PIN_NUMBER      24u
#define LEDpin1_CONFIG_DO_PIN_MUXING   1


//#endif /* SRC_INCLUDEMCULIBCONFIG_H_ */
