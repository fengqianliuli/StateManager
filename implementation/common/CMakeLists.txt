################################################################################
# Common Header
################################################################################
add_library(common_header INTERFACE)
target_include_directories(common_header INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)
target_link_libraries(common_header INTERFACE glog::glog)
