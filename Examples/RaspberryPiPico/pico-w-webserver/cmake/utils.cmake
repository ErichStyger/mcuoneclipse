# see https://github.com/raspberrypi/pico-sdk/issues/780
function(suppress_tinyusb_warnings)
        set_source_files_properties(
                ${PICO_TINYUSB_PATH}/src/portable/raspberrypi/rp2040/rp2040_usb.c
                PROPERTIES
                COMPILE_FLAGS "-Wno-stringop-overflow -Wno-array-bounds")
endfunction()

function(get_pico_sdk_import_cmake)
        set(PICO_SDK_IMPORT_CMAKE ${CMAKE_CURRENT_FUNCTION_LIST_DIR}/pico_sdk_import.cmake)

        if (NOT EXISTS ${PICO_SDK_IMPORT_CMAKE})
                file(DOWNLOAD
                        https://raw.githubusercontent.com/raspberrypi/pico-sdk/2e6142b15b8a75c1227dd3edbe839193b2bf9041/external/pico_sdk_import.cmake
                        ${PICO_SDK_IMPORT_CMAKE}
                        )
        endif()
endfunction()
