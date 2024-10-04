# file: Collect all files that need to be compiled. 
# You can use a GLOB function as shown here, or explicitly mention the specific files
#file(GLOB FILES *.c *.h)

set(THIS_LIBRARY_NAME pico_pio_usb)
add_library(${THIS_LIBRARY_NAME} INTERFACE)

set(dir .)

# generate PIO header inside the src directory. Note: touch this CMakeLists.txt or *.pio to enforce generating the header file.
pico_generate_pio_header(${THIS_LIBRARY_NAME} ${CMAKE_CURRENT_LIST_DIR}/usb_rx.pio)
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/usb_rx.pio.h)
  file(COPY ${CMAKE_CURRENT_BINARY_DIR}/usb_rx.pio.h DESTINATION ${CMAKE_CURRENT_LIST_DIR})  # copy file from the build folder to the src folder  
endif()
pico_generate_pio_header(${THIS_LIBRARY_NAME} ${CMAKE_CURRENT_LIST_DIR}/usb_tx.pio)
if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/usb_tx.pio.h)
  file(COPY ${CMAKE_CURRENT_BINARY_DIR}/usb_tx.pio.h DESTINATION ${CMAKE_CURRENT_LIST_DIR})  # copy file from the build folder to the src folder  
endif()

target_sources(${THIS_LIBRARY_NAME} INTERFACE
    ${dir}/pio_usb.c
    ${dir}/pio_usb_device.c
    ${dir}/pio_usb_host.c
    ${dir}/usb_crc.c
)

target_link_libraries(${THIS_LIBRARY_NAME} INTERFACE
    pico_stdlib
    pico_multicore
    hardware_pio
    hardware_dma
)

target_include_directories(${THIS_LIBRARY_NAME} INTERFACE ${dir})

# enable all warnings
#target_compile_options(${THIS_LIBRARY_NAME} INTERFACE -Wall -Wextra)
