################################################################################
# State Manager Library
################################################################################
file(GLOB state_manager_SRC
    "*.cpp"
)
list(SORT state_manager_SRC)

add_library(state_manager SHARED ${state_manager_SRC})
set_target_properties (state_manager PROPERTIES VERSION ${SM_VERSION} SOVERSION ${SM_MAJOR_VERSION})

target_link_libraries(state_manager configuration common_header)
install(TARGETS state_manager LIBRARY DESTINATION lib)
