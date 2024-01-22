################################################################################
# Communication Server Library
################################################################################
file(GLOB server_SRC
    "server/*.cpp"
)
list(SORT server_SRC)

add_library(server SHARED ${server_SRC})
set_target_properties (server PROPERTIES VERSION ${SM_VERSION} SOVERSION ${SM_MAJOR_VERSION})

target_link_libraries(server common_header vsomeip3)
install(TARGETS server LIBRARY DESTINATION lib)


################################################################################
# Communication Test App
################################################################################
file(GLOB test_app_SRC
    "test/*.cpp"
)
list(SORT test_app_SRC)

add_executable(test_app ${test_app_SRC})

target_link_libraries(test_app server common_header)

install(TARGETS test_app DESTINATION bin)
