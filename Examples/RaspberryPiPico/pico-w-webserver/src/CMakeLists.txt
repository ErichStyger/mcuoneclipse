set(PROGRAM_NAME pico_w_webserver)

set(MAKE_FS_DATA_SCRIPT ${CMAKE_CURRENT_LIST_DIR}/external/makefsdata)

if (NOT EXISTS ${MAKE_FS_DATA_SCRIPT})
        file(DOWNLOAD
                https://raw.githubusercontent.com/krzmaz/lwip/e15654409d14a238aec5ed4bd5516063938c9345/src/apps/http/makefsdata/makefsdata
                ${MAKE_FS_DATA_SCRIPT}
                )
endif()
message("Running makefsdata script")
execute_process(COMMAND
        makefsdata/makefsdata.exe
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        ECHO_OUTPUT_VARIABLE
        ECHO_ERROR_VARIABLE
        )
file(RENAME fsdata.c my_fsdata.c)

add_executable(${PROGRAM_NAME}
        main.cpp
        ssi.cpp
        cgi.cpp
        )
target_compile_definitions(${PROGRAM_NAME} PRIVATE
        WIFI_SSID=\"${WIFI_SSID}\"
        WIFI_PASSWORD=\"${WIFI_PASSWORD}\"
        )
target_include_directories(${PROGRAM_NAME} PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        )
target_link_libraries(${PROGRAM_NAME}
        #cyw43_driver_base
        pico_cyw43_arch_lwip_threadsafe_background
        pico_lwip_http
        pico_stdlib
        hardware_adc
        )

pico_enable_stdio_usb(${PROGRAM_NAME} TRUE)
pico_enable_stdio_uart(${PROGRAM_NAME} TRUE)
suppress_tinyusb_warnings()

pico_add_extra_outputs(${PROGRAM_NAME})
