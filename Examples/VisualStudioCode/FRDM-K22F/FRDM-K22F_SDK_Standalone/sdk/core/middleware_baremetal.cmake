#Description: middleware_baremetal; user_visible: True
include_guard(GLOBAL)
message("middleware_baremetal component is included.")

target_sources(${MCUX_SDK_PROJECT_NAME} PRIVATE
)

target_include_directories(${MCUX_SDK_PROJECT_NAME} PUBLIC
)


