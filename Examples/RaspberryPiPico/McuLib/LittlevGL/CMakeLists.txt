# file: Collect all files that need to be compiled. 

# search recursively all files:
file(GLOB_RECURSE LVGL_FILES "lvgl/src/*.c")

# add_library: With this declaration, you express the intent to build a library. 
# The first argument, is the name of the library, 
# the second argument are the files that will be compiled to create your library.
add_library(lvglLib 
  ${LVGL_FILES}
)

# target_link_libraries: If you link with other libraries, list them here
target_link_libraries(
  lvglLib 
)

# target_include_directories: Libraries need to publish their header files 
# so that you can import them in source code. This statement expresses where to find the files 
# - typically in an include directory of your projects.
target_include_directories(
  lvglLib 
  PUBLIC
  ./
  ./lvgl
 )
 