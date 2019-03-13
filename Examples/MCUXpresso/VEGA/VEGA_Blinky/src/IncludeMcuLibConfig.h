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

/* green LED */
#define McuLED2_CONFIG_IS_LOW_ACTIVE   (0)
#define LEDpin2_CONFIG_GPIO_NAME       GPIOA
#define LEDpin2_CONFIG_PORT_NAME       PORTA
#define LEDpin2_CONFIG_PIN_NUMBER      23u
#define LEDpin2_CONFIG_DO_PIN_MUXING   1

/* blue LED */
#define McuLED3_CONFIG_IS_LOW_ACTIVE   (0)
#define LEDpin3_CONFIG_GPIO_NAME       GPIOA
#define LEDpin3_CONFIG_PORT_NAME       PORTA
#define LEDpin3_CONFIG_PIN_NUMBER      22u
#define LEDpin3_CONFIG_DO_PIN_MUXING   1

/* sts LED */
#define McuLED4_CONFIG_IS_LOW_ACTIVE   (0)
#define LEDpin4_CONFIG_GPIO_NAME       GPIOE
#define LEDpin4_CONFIG_PORT_NAME       PORTE
#define LEDpin4_CONFIG_PIN_NUMBER      0u
#define LEDpin4_CONFIG_DO_PIN_MUXING   1

//#endif /* SRC_INCLUDEMCULIBCONFIG_H_ */
