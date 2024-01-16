################################################################################
# Plugin Manager Library
################################################################################
file(GLOB plugin_manager_SRC
    "*.cpp"
)
list(SORT plugin_manager_SRC)

add_library(plugin_manager SHARED ${plugin_manager_SRC})
set_target_properties (plugin_manager PROPERTIES VERSION ${SM_VERSION} SOVERSION ${SM_MAJOR_VERSION})

target_link_libraries(plugin_manager class_loader_manager common)
install(TARGETS plugin_manager LIBRARY DESTINATION lib)
