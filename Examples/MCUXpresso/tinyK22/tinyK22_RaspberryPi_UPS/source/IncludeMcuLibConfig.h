
/* header file is included with -include compiler option */

/* tinyK22 with hardware V3 only! */
#define McuLib_CONFIG_SDK_VERSION_USED  McuLib_CONFIG_SDK_MCUXPRESSO_2_0
#define McuLib_CONFIG_SDK_USE_FREERTOS  (1)

#define PINS_HATNAVUP_GPIO      GPIOB
#define PINS_HATNAVUP_PORT      PORTB
#define PINS_HATNAVUP_PIN       0u

#define PINS_HATNAVDOWN_GPIO    GPIOB
#define PINS_HATNAVDOWN_PORT    PORTB
#define PINS_HATNAVDOWN_PIN     1u

#define PINS_HATNAVLEFT_GPIO    GPIOB
#define PINS_HATNAVLEFT_PORT    PORTB
#define PINS_HATNAVLEFT_PIN     3u

#define PINS_HATNAVRIGHT_GPIO   GPIOB
#define PINS_HATNAVRIGHT_PORT   PORTB
#define PINS_HATNAVRIGHT_PIN    2u

#define PINS_HATNAVPUSH_GPIO    GPIOB
#define PINS_HATNAVPUSH_PORT    PORTB
#define PINS_HATNAVPUSH_PIN     16u

/* LEDs on HAT: */
  /* LED blue: PTC8
   * LED green: PTC9
   * LED yellow: PTC10
   * LED red: PTC11
   */
/* LED on tinyK22 */
#define PINS_LEDBLUE_GPIO       GPIOC
#define PINS_LEDBLUE_PORT       PORTC
#define PINS_LEDBLUE_PIN        2U

#define PINS_HATLEDBLUE_GPIO    GPIOC
#define PINS_HATLEDBLUE_PORT    PORTC
#define PINS_HATLEDBLUE_PIN     8U

#define PINS_HATLEDGREEN_GPIO   GPIOC
#define PINS_HATLEDGREEN_PORT   PORTC
#define PINS_HATLEDGREEN_PIN    9U

#define PINS_HATLEDYELLOW_GPIO  GPIOC
#define PINS_HATLEDYELLOW_PORT  PORTC
#define PINS_HATLEDYELLOW_PIN   10U

#define PINS_HATLEDRED_GPIO     GPIOC
#define PINS_HATLEDRED_PORT     PORTC
#define PINS_HATLEDRED_PIN      11U

#define PINS_ALERT_GPIO     GPIOD
#define PINS_ALERT_PORT     PORTD
#define PINS_ALERT_PIN      3U

/* LPUART to OpenSDA */
#define PINS_LPUART0_RX_PORT PORTC
#define PINS_LPUART0_RX_PIN  3U

#define PINS_LPUART0_TX_PORT PORTC
#define PINS_LPUART0_TX_PIN  4U

/* OLED */
/* ------------------- I2C ---------------------------*/
/* pins used */
#define SCL1_CONFIG_GPIO_NAME     GPIOA
#define SCL1_CONFIG_PORT_NAME     PORTA
#define SCL1_CONFIG_PIN_NUMBER    12u

#define SDA1_CONFIG_GPIO_NAME     GPIOA
#define SDA1_CONFIG_PORT_NAME     PORTA
#define SDA1_CONFIG_PIN_NUMBER    13u

/* I2C Pin Muxing */
#define SDA1_CONFIG_DO_PIN_MUXING (1)
#define SCL1_CONFIG_DO_PIN_MUXING (1)

/* no RTOS, no MUTEX */
#define McuGenericI2C_CONFIG_USE_MUTEX          (0)

/* no RTOS, no Yield */
#define McuGenericSWI2C_CONFIG_DO_YIELD (0) /* because of Yield in GenericSWI2C */

/* not interested in error events */
#define McuGenericI2C_CONFIG_USE_ON_ERROR_EVENT (0)

/* just for speed */
#define McuGenericSWI2C_CONFIG_DELAY_NS (0)

#if 1 /* type of LCD received */
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1106)
#else
  #define McuSSD1306_CONFIG_SSD1306_DRIVER_TYPE  (1306)
#endif

