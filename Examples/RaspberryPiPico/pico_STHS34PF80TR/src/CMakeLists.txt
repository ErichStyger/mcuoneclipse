# file: Collect all files that need to be compiled. 
# You can use a GLOB function as shown here, or explicitly mention the specific files
#file(GLOB FILES *.c *.h)

# Need to include CTest on every CMakeLists.txt which is going to use tests
include(CTest)

set(THIS_LIBRARY_NAME srcLib)

file(GLOB FILES
  *.c
)

if (ENABLE_UNIT_TESTING)
  message(STATUS "Adding src tests")
  add_subdirectory(./tests                  tests)
endif()

# add_library: With this declaration, you express the intent to build a library. 
# The first argument is the name of the library,
# the second argument are the files that will be compiled to create your library.
add_library(${THIS_LIBRARY_NAME} ${FILES})

add_subdirectory(${MCULIB_DIR}          McuLib)

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(
  ${THIS_LIBRARY_NAME}
  PRIVATE McuLib
  PRIVATE tinyusb_device

  PRIVATE pico_stdlib
# For PicoW, select the library to be used:
# PRIVATE pico_cyw43_arch_none     # we need CYW43 to access the GPIO, but we don't need anything else
# PRIVATE pico_cyw43_arch_lwip_sys_freertos  # full lwIP including blocking sockets, with NO_SYS=0 in lwipopts.h
)

if (ENABLE_UNIT_TESTING)
  message(STATUS "Adding src tests library")
  target_link_libraries(
    ${THIS_LIBRARY_NAME}
    PUBLIC srcTestsLib
  )
endif()

# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(
  ${THIS_LIBRARY_NAME}
  PUBLIC
  .
)
