################################################################################
# Example Plugin Library
################################################################################
file(GLOB example_plugin_SRC
    "*.cpp"
)
list(SORT example_plugin_SRC)

add_library(example_plugin SHARED ${example_plugin_SRC})
set_target_properties (example_plugin PROPERTIES VERSION ${SM_VERSION} SOVERSION ${SM_MAJOR_VERSION})

target_link_libraries(example_plugin class_loader_manager state_manager)

install(TARGETS example_plugin LIBRARY DESTINATION sm_plugin_lib)
