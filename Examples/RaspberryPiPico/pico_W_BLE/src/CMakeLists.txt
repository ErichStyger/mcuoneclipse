# file: Collect all files that need to be compiled. 
file(GLOB FILES
  *.c
)

# add_library: With this declaration, you express the intent to build a library. 
# The first argument is the name of the library, 
# the second argument are the files that will be compiled to create your library.
add_library(SrcLib ${FILES})

# need to add custom compile flags
target_compile_definitions(SrcLib PRIVATE
  CYW43_ENABLE_BLUETOOTH=1  # otherwise cyw43_arch_init() will not initialize BLE
)

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(
  SrcLib                # this library
  PRIVATE McuLib                # we need the McuLib
  PRIVATE pico_stdlib           # pico standard library
  PRIVATE hardware_adc          # internal temperature and ADC
  PRIVATE pico_btstack_ble      # BLE stack
  PRIVATE pico_btstack_cyw43    # BLE stack with CYW43
  PRIVATE pico_cyw43_arch_lwip_sys_freertos  # full lwIP stack including blocking sockets, with NO_SYS=0
)

# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(SrcLib PUBLIC .)

# run the compile_gatt compiler to create a GATT file from the BTstack GATT file:
pico_btstack_make_gatt_header(SrcLib PRIVATE "${CMAKE_CURRENT_LIST_DIR}/temp_sensor.gatt")
