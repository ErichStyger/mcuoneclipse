# file: Collect all files that need to be compiled. 
# You can use a GLOB function as shown here, or explicitly mention the specific files
#file(GLOB FILES *.c *.h)

file(GLOB FILES
  *.c
 )

# generate PIO header "ws2812.pio.h" inside the src directory
pico_generate_pio_header(${PROJECT_NAME} ${CMAKE_CURRENT_LIST_DIR}/ws2812.pio)

# add_library: With this declaration, you express the intent to build a library. 
# The first argument is the name of the library, 
# the second argument are the files that will be compiled to create your library.
add_library(SrcLib ${FILES}) 

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(
  SrcLib 
  McuLib 
  pico_stdlib
#  pico_cyw43_arch_none     # we need CYW43 to access the GPIO, but we don't need anything else
#  # pico_cyw43_arch_lwip_poll
# pico_cyw43_arch_lwip_threadsafe_background  # RAW lwIP with NO_SYS=1 in lwipopts.h
#  pico_cyw43_arch_lwip_sys_freertos  # full lwIP including blocking sockets, with NO_SYS=0 in lwipopts.h
  hardware_pio # PIO for WS2812B
  hardware_dma
)

# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(SrcLib PUBLIC .)
