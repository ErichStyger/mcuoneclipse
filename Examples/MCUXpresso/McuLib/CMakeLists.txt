
if (DEFINED PICO_BOARD) 
  message(STATUS "McuLib for RP2040")
  INCLUDE (RP2040_CMakeLists.txt)
else ()
  message(STATUS "McuLib for ESP32")
  INCLUDE (ESP32_CMakeLists.txt)
endif ()


######################################################
# MCULIB_TARGET needs to be set in main CMakeList.txt, for example:
#set(
#    MCULIB_TARGET RP2040 CACHE STRING 
#    "Select McuLib target: RP2040 or ESP32"
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
