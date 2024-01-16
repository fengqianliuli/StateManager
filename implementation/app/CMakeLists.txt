################################################################################
# State Manager App
################################################################################
file(GLOB state_manager_app_SRC
    "*.cpp"
)
list(SORT state_manager_app_SRC)

add_executable(state_manager_app ${state_manager_app_SRC})

target_link_libraries(state_manager_app state_manager)

install(TARGETS state_manager_app DESTINATION bin)
install(DIRECTORY ${CONFIG_DIR}/ DESTINATION config)
