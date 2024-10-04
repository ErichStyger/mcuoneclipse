# file: Collect all files that need to be compiled. 
# You can use a GLOB function as shown here, or explicitly mention the specific files
#file(GLOB FILES *.c *.h)

set(THIS_LIBRARY_NAME srcLib)

file(GLOB FILES
  *.c
  # Enable for PL_CONFIG_USE_USB_HOST_MODE:
  # can use 'tinyusb_pico_pio_usb' library later when pico-sdk is updated
  ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/pio_usb/dcd_pio_usb.c
  ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/pio_usb/hcd_pio_usb.c
)

# add_library: With this declaration, you express the intent to build a library.
# The first argument is the name of the library,
# the second argument are the files that will be compiled to create your library.
add_library(${THIS_LIBRARY_NAME} ${FILES})

add_subdirectory(${MCULIB_DIR}          McuLib)
add_subdirectory(${MCULIB_DIR}/rdimon   rdimon)

# Enable for PL_CONFIG_USE_USB_HOST_MODE:
set(PICO_PIO_USB_DIR "${CMAKE_CURRENT_LIST_DIR}/../pico_pio_usb")
add_subdirectory(${PICO_PIO_USB_DIR} pico_pio_usb)
# the second argument to add_subdirectory is needed here because this isn't
# a subdirectory, it's out of tree.

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(
  ${THIS_LIBRARY_NAME}
  PRIVATE McuLib

  # Disable for PL_CONFIG_USE_USB_HOST_MODE:
  #PRIVATE pico_stdlib
  #PRIVATE pico_stdio_semihosting
  #PRIVATE pico_stdio_usb
  #PRIVATE pico_stdio_uart

  # Enable for PL_CONFIG_USE_USB_HOST_MODE:
  PUBLIC pico_pio_usb
  PUBLIC tinyusb_device
  PUBLIC tinyusb_host
  PUBLIC pico_multicore
  PUBLIC hardware_pio
  PUBLIC hardware_dma

  PUBLIC rdimonLib # file I/O with semihosting
)

# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(
  ${THIS_LIBRARY_NAME}
  PUBLIC
  .
)
