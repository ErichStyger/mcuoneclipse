# file: Collect all files that need to be compiled. 
# You can use a GLOB function as shown here, or explicitly mention the specific files
#file(GLOB FILES *.c *.h)

#set(CMAKE_VERBOSE_MAKEFILE ON) # for verbose output

file(GLOB FILES
  main.c
  app_platform.c
  application.c
  Shell.c
  FreeRTOShooks.c
  myBLE.c
  client.c
  server.c
  server_common.c
  server_with_wifi.c
  picow_bt_example_common.c
  picow_bt_example_poll.c
)

# generate PIO header "ws2812.pio.h" inside the src directory
#pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

# add_library: With this declaration, you express the intent to build a library. 
# The first argument is the name of the library, 
# the second argument are the files that will be compiled to create your library.
add_library(SrcLib ${FILES})

target_compile_definitions(SrcLib PRIVATE
  CYW43_ENABLE_BLUETOOTH=1  # otherwise cyw43_arch_init() will not initialize BLE
#  CYW43_LWIP=0
)

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(
  SrcLib 
  McuLib 
  pico_stdlib
  hardware_pio  # WS2812B
  hardware_adc  # internal temperature and ADC
  hardware_rtc  # RTC for sleep.c
  hardware_spi  # for SPI (external flash) 
  
  pico_btstack_ble
  pico_btstack_cyw43
  pico_cyw43_arch_none

#pico_btstack_bnep_lwip_sys_freertos  # Adds Bluetooth Network Encapsulation Protocol (BNEP) support using LwIP with FreeRTOS for NO_SYS=0.
#  cyw43_driver_picow
#  pico_btstack_run_loop_async_context
#  pico_btstack_sbc_encoder # Adds Bluetooth Sub Band Coding (SBC) encoder support (audio).
#  pico_btstack_sbc_decoder # Adds Bluetooth Sub Band Coding (SBC) decoder support (audio).
#pico_cyw43_arch_lwip_threadsafe_background
  
#  #pico_cyw43_arch_none     # we need Wifi to access the GPIO, but we don't need anything else
#  # pico_cyw43_arch_lwip_poll
#  # pico_cyw43_arch_lwip_threadsafe_background  # RAW lwIP with NO_SYS=1
#pico_cyw43_arch_lwip_sys_freertos  # full lwIP including blocking sockets, with NO_SYS=0
#pico_btstack_bnep_lwip_sys_freertos
  
# add common stuff for BLE
#  pico_btstack_ble # Adds Bluetooth Low Energy (LE) support.
#  pico_btstack_classic
# pico_btstack_cyw43

#  pico_cyw43_arch_sys_freertos
#  pico_btstack_bnep_lwip_sys_freertos
#  pico_lwip_freertos
)


# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(SrcLib PUBLIC .)

pico_btstack_make_gatt_header(SrcLib PRIVATE "${CMAKE_CURRENT_LIST_DIR}/temp_sensor.gatt")
