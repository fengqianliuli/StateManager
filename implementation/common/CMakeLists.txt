################################################################################
# Common Header
################################################################################
add_library(common_header INTERFACE)
target_include_directories(common_header INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(common_header INTERFACE glog::glog)


################################################################################
# Common Library
################################################################################
file(GLOB common_SRC
    "*.cpp"
)
list(SORT common_SRC)

add_library(common SHARED ${common_SRC})
set_target_properties (common PROPERTIES VERSION ${SM_VERSION} SOVERSION ${SM_MAJOR_VERSION})

target_link_libraries(common common_header)
install(TARGETS common LIBRARY DESTINATION lib)