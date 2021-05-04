
cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(MyProject VERSION 1.0)

# add the executable
add_executable(MyProject main.c)

#configure_file(TutorialConfig.h.in TutorialConfig.h)

#target_include_directories(MyProject PUBLIC
#                           "${PROJECT_BINARY_DIR}"
#                           )

set(LINKER_SCRIPT "../linker.ld")

include(cmake/efr32mg.cmake)
