include_directories(${CMAKE_SOURCE_DIR}/implementation
                    ${CMAKE_SOURCE_DIR}/interface)

add_subdirectory(common)
add_subdirectory(class_loader)
add_subdirectory(configuration)
add_subdirectory(plugin_manager)
add_subdirectory(plugins)
add_subdirectory(state_manager)
add_subdirectory(app)
