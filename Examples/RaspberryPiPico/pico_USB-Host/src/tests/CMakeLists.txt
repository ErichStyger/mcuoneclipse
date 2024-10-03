# file: Collect all files that need to be compiled. 
# You can use a GLOB function as shown here, or explicitly mention the specific files
#file(GLOB FILES *.c *.h)

# Need to include CTest on every CMakeLists.txt which is going to use tests
include(CTest)

set(THIS_LIBRARY_NAME srcTestsLib)

file(GLOB FILES
  *.c
)

# add_library: With this declaration, you express the intent to build a library. 
# The first argument is the name of the library, 
# the second argument are the files that will be compiled to create your library.
add_library(${THIS_LIBRARY_NAME} ${FILES})

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(
  ${THIS_LIBRARY_NAME}
  PRIVATE McuLib
  PRIVATE srcLib
  PRIVATE unityLib
)

# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(
  ${THIS_LIBRARY_NAME}
  PUBLIC
  .
)
#################################################################################
# Note: --ipc off --isp off are needed, if application runs from the ROM bootloader
set (JRUN_CTEST_COMMAND "$ENV{SEGGER_PATH}/JRun" --verbose --device RP2040_M0_0 --rtt -if SWD --pc off --sp off)

set (passRegex "\\*\\* PASSED \\*\\*\\*")
set (failRegex "\\*\\*\\* FAILED \\*\\*\\*")
set_property(TEST PROPERTY PASS_REGULAR_EXPRESSION "${passRegex}")
set_property(TEST PROPERTY FAIL_REGULAR_EXPRESSION "${failRegex}")

add_test(
  NAME Led_1
  #COMMAND ${JRUN_CTEST_COMMAND} --jlinkscriptfile "${CMAKE_CURRENT_SOURCE_DIR}/test_1.JLinkScript" ${TEST_EXECUTABLE}
  COMMAND ${JRUN_CTEST_COMMAND} --args "Led_1" ${TEST_EXECUTABLE}
)

add_test(
  NAME Led_2
  #COMMAND ${JRUN_CTEST_COMMAND} --jlinkscriptfile "${CMAKE_CURRENT_SOURCE_DIR}/test_2.JLinkScript" ${TEST_EXECUTABLE}
  COMMAND ${JRUN_CTEST_COMMAND} --args "Led_2" ${TEST_EXECUTABLE}
)

set_tests_properties(Led_1 Led_2 PROPERTIES TIMEOUT 120) 
set_tests_properties(Led_1 Led_2 PROPERTIES PASS_REGULAR_EXPRESSION "${passRegex}") 
set_tests_properties(Led_1 Led_2 PROPERTIES FAIL_REGULAR_EXPRESSION "${failRegex}") 
