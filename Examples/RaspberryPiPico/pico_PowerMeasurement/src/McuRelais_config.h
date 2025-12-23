#ifndef McuRelais_CONFIG_H_
#define McuRelais_CONFIG_H_

#ifndef McuRelais_CONFIG_PARSE_COMMAND_ENABLED
  #define McuRelais_CONFIG_PARSE_COMMAND_ENABLED    (1)
  /*!< If shell parser is enabled (1) or not (0). */
#endif

#ifndef McuRelais_CONFIG_PIN_SET
  #define McuRelais_CONFIG_PIN_SET                  (0x08u)
  /*!< GPIO pin number for setting the release */
#endif

#ifndef McuRelais_CONFIG_PIN_RESET
  #define McuRelais_CONFIG_PIN_RESET                (0x09u)
  /*!< GPIO pin number for resetting the release */
#endif

#ifndef McuRelais_CONFIG_PULSE_TIME_MS
  #define McuRelais_CONFIG_PULSE_TIME_MS            (0x32)
  /*!< 50ms pulse time */
#endif

#endif /* McuRelais_CONFIG_H_ */
