##
## Author:  Johannes Bruder
## License:  See LICENSE.TXT file included in the project
##
## Collection of functions to generate different GDB debugging configurations
##

# Get the path of this module
set(CURRENT_MODULE_DIR ${CMAKE_CURRENT_LIST_DIR})

#---------------------------------------------------------------------------------------
# Set tools
#---------------------------------------------------------------------------------------
set(GDB_BIN ${TOOLCHAIN_BIN_DIR}/${TOOLCHAIN}-gdb${TOOLCHAIN_EXT})
if(NOT OPENOCD_BIN)
        if(CMAKE_HOST_SYSTEM_NAME STREQUAL Linux)
            set(OPENOCD_BIN "/usr/bin/openocd" CACHE STRING "OpenOCD executable")
        elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Darwin)
            set(OPENOCD_BIN "/usr/local/bin/openocd" CACHE STRING "OpenOCD executable")
        elseif(CMAKE_HOST_SYSTEM_NAME STREQUAL Windows)
            set(OPENOCD_BIN "C:/openocd/bin/openocd.exe" CACHE STRING "OpenOCD executable")
        endif()
endif()

#---------------------------------------------------------------------------------------
# Generates a GDB run script for debugging with STLINKv1/v2/v2-1 programmer and texane stlink tool.
# More infos check: https://github.com/texane/stlink
#---------------------------------------------------------------------------------------
function(generate_run_gdb_stlink TARGET)
    get_target_property( TARGET_NAME ${TARGET} NAME )
    configure_file(${CURRENT_MODULE_DIR}/stlink-run.gdb.in ${PROJECT_BINARY_DIR}/stlink-run.gdb @ONLY)
endfunction()

#---------------------------------------------------------------------------------------
# Generates a GDB run script for debugging with any supported programmer and openOCD.
#---------------------------------------------------------------------------------------
function(generate_run_gdb_openocd TARGET)
    get_target_property( TARGET_NAME ${TARGET} NAME )
    configure_file(${CURRENT_MODULE_DIR}/openocd-run.gdb.in ${PROJECT_BINARY_DIR}/openocd-run.gdb @ONLY)
endfunction()
