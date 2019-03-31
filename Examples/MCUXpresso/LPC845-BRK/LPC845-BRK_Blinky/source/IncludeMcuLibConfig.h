/* header file is included with -include compiler option */

/* LPC845-BRK */

#define McuLib_CONFIG_CPU_IS_KINETIS  (0)
#define McuLib_CONFIG_CPU_IS_LPC      (1)
#define McuLib_CONFIG_CORTEX_M      (0)


#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_SDK_USE_FREERTOS  (0)

/* LEDs on LPC845-BRK */
#define PINS_LEDGREEN_GPIO       GPIO
#define PINS_LEDGREEN_PORT       1U
#define PINS_LEDGREEN_PIN        0U
/* LEDpin1 */
//#define BOARD_INITPINS_LEDpin1_GPIO  PINS_LEDGREEN_GPIO
//#define LEDpin1_CONFIG_PORT_NAME  PINS_LEDGREEN_PORT
//#define LEDpin1_CONFIG_PIN_NUMBER PINS_LEDGREEN_PIN

#define PINS_LEDBLUE_GPIO       GPIO
#define PINS_LEDBLUE_PORT       1U
#define PINS_LEDBLUE_PIN        1U
/* LEDpin2 */
//#define LEDpin2_CONFIG_GPIO_NAME  PINS_LEDBLUE_GPIO
//#define LEDpin2_CONFIG_PORT_NAME  PINS_LEDBLUE_PORT
//#define LEDpin2_CONFIG_PIN_NUMBER PINS_LEDBLUE_PIN

#define PINS_LEDRED_GPIO       GPIO
#define PINS_LEDRED_PORT       1U
#define PINS_LEDRED_PIN        1U
/* LEDpin3 */
//#define LEDpin3_CONFIG_GPIO_NAME  PINS_LEDRED_GPIO
//#define LEDpin3_CONFIG_PORT_NAME  PINS_LEDRED_PORT
//#define LEDpin3_CONFIG_PIN_NUMBER PINS_LEDRED_PIN

/* Buttons */
/* PIO0_4 */
#define PINS_BTNK3_GPIO       GPIO
#define PINS_BTNK3_PORT       0U
#define PINS_BTNK3_PIN        4U

/* PIO0_12 */
#define PINS_BTNK1_GPIO       GPIO
#define PINS_BTNK1_PORT       0U
#define PINS_BTNK1_PIN        12U
