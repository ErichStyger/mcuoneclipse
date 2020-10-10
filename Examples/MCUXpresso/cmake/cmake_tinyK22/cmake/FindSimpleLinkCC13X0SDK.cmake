##
## Author:   Johannes Bruder
## License:  See LICENSE.TXT file included in the project
##
## Find TI's SimpleLink CC13X0 SDK
## 

include(FindPackageHandleStandardArgs)

find_path(SimpleLinkCC13X0SDK_DEVICES_DIR NAMES "DeviceFamily.h" PATH_SUFFIXES "source/ti/devices")

# Add suffix when looking for libraries
list(APPEND CMAKE_FIND_LIBRARY_SUFFIXES "am3g" "lib")

# Find TI's drivers lib
find_library(SimpleLinkCC13X0SDK_drivers_cc13x0_LIBRARY
    NAMES drivers_cc13x0.am3g
    PATH_SUFFIXES "source/ti/drivers/lib"
)

# Find cc13x0 radio multi mode lib
find_library(SimpleLinkCC13X0SDK_rf_multiMode_cc13x0_LIBRARY
    NAMES rf_multiMode_cc13x0.am3g
    PATH_SUFFIXES "source/ti/drivers/rf/lib"
)

# Find driver porting layer (FreeRTOS/TIRTOS) lib
find_library(SimpleLinkCC13X0SDK_dpl_cc13x0_LIBRARY
    NAMES dpl_cc13x0.am3g
    PATH_SUFFIXES "kernel/tirtos/packages/ti/dpl/lib"
)

# Find Driverlib
find_library(SimpleLinkCC13X0SDK_driverlib_LIBRARY
    NAMES driverlib.lib
    PATH_SUFFIXES "source/ti/devices/cc13x0/driverlib/bin/gcc"
)

set(SimpleLinkCC13X0SDK_INCLUDE_DIRS
    "${SimpleLinkCC13X0SDK_DEVICES_DIR}/../.."
    "${SimpleLinkCC13X0SDK_DEVICES_DIR}/../../../kernel/tirtos/packages/ti/sysbios/posix"
    "${SimpleLinkCC13X0SDK_DEVICES_DIR}/../../../kernel/tirtos/packages"
)
message("Content of SimpleLinkCC13X0SDK_INCLUDE_DIRS " ${SimpleLinkCC13X0SDK_INCLUDE_DIRS})

# Handle arguments and set SimpleLinkCC13X0SDK_FOUND to TRUE if all listed variables are TRUE
find_package_handle_standard_args(SimpleLinkCC13X0SDK  DEFAULT_MSG
    SimpleLinkCC13X0SDK_drivers_cc13x0_LIBRARY
    SimpleLinkCC13X0SDK_rf_multiMode_cc13x0_LIBRARY
    SimpleLinkCC13X0SDK_dpl_cc13x0_LIBRARY
    SimpleLinkCC13X0SDK_driverlib_LIBRARY
    SimpleLinkCC13X0SDK_INCLUDE_DIRS
)

set(SimpleLinkCC13X0SDK_LIBRARIES
    ${SimpleLinkCC13X0SDK_drivers_cc13x0_LIBRARY}
    ${SimpleLinkCC13X0SDK_rf_multiMode_cc13x0_LIBRARY}
    ${SimpleLinkCC13X0SDK_dpl_cc13x0_LIBRARY}
    ${SimpleLinkCC13X0SDK_driverlib_LIBRARY}
)
