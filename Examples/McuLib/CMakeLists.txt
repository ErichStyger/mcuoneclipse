
if (DEFINED PICO_BOARD) 
    message(STATUS "McuLib for RP2040")
    INCLUDE (RP2040_CMakeLists.txt)
elseif ( MCULIB_TARGET STREQUAL "MCUXPRESSO" )
    message(STATUS "McuLib for MCUXpresso SDK")
    INCLUDE (MCUXpresso_CMakeLists.txt)
else ()
    message(STATUS "McuLib for ESP32")
    # Espressif IDF CMake files are special: cannot include sub file here.
    idf_component_register(
          SRCS 
              "fonts/McuFontCour08Bold.c"
              "fonts/McuFontCour08Normal.c"
              "fonts/McuFontCour10Bold.c"
              "fonts/McuFontCour10Normal.c"
              "fonts/McuFontCour12Bold.c"
              "fonts/McuFontCour12Normal.c"
              "fonts/McuFontCour14Bold.c"
              "fonts/McuFontCour14Normal.c"
              "fonts/McuFontCour18Bold.c"
              "fonts/McuFontCour18Normal.c"
              "fonts/McuFontCour24Bold.c"
              "fonts/McuFontCour24Normal.c"
              "fonts/McuFontHelv08Bold.c"
              "fonts/McuFontHelv08Normal.c"
              "fonts/McuFontHelv10Bold.c"
              "fonts/McuFontHelv10Normal.c"
              "fonts/McuFontHelv12Bold.c"
              "fonts/McuFontHelv12Normal.c"
              "fonts/McuFontHelv14Bold.c"
              "fonts/McuFontHelv14Normal.c"
              "fonts/McuFontHelv18Bold.c"
              "fonts/McuFontHelv18Normal.c"
              "fonts/McuFontHelv24Bold.c"
              "fonts/McuFontHelv24Normal.c"
              
              "RNet/McuNRF24L01.c"
              "RNet/McuRNet.c"
              "RNet/Radio.c"
              "RNet/RApp.c"
              "RNet/RMAC.c"
              "RNet/RMSG.c"
              "RNet/RNWK.c"
              "RNet/RPHY.c"
              "RNet/RStack.c"
              "RNet/RStdio.c"
              
              "src/McuArmTools.c"
              "src/McuButton.c"
              "src/McuCriticalSection.c"
              "src/McuDebounce.c"
              "src/McuFXOS8700.c"
              "src/McuFontDisplay.c"
              "src/McuGenericI2C.c"
              "src/McuGDisplaySSD1306.c"
              "src/McuGPIO.c"
              "src/McuGFont.c"
              "src/McuI2cLib.c"
              "src/McuLib.c"
              "src/McuLED.c"
              "src/McuLog.c"
              "src/McuRB.c"
              "src/McuRTOS.c"
              "src/McuShell.c"
              "src/McuSPI.c"
              "src/McuSHT31.c"
              "src/McuSHT40.c"
              "src/McuSSD1306.c"
              "src/McuTimeDate.c"
              "src/McuTimeout.c"
              "src/McuTrigger.c"
              "src/McuUart485.c"
              "src/McuUtility.c"
              "src/McuWait.c"
              "src/McuXFormat.c"
          INCLUDE_DIRS
              "./"
              "./config"
              "./src"
              "./fonts"
              "./config/fonts"
          REQUIRES
              driver
         )
   
endif ()


######################################################
# MCULIB_TARGET needs to be set in main CMakeList.txt, for example:
#set(
#    MCULIB_TARGET RP2040 CACHE STRING 
#    "Select McuLib target: RP2040, MCUXPRESSO or ESP32"
#)
#
######################################################
# if ( MCULIB_TARGET STREQUAL "ESP32" )
#  message(STATUS "McuLib for ESP32")
#  INCLUDE (ESP32_CMakeLists.txt)
# elseif ( MCULIB_TARGET STREQUAL "RP2040" )
#  message(STATUS "McuLib for RP2040")
#  INCLUDE (RP2040_CMakeLists.txt)
# else ()
#  message ( STATUS "Unknown McuLib target: ${MCULIB_TARGET}" )
# endif ()
######################################################
