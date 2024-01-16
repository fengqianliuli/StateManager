################################################################################
# Configuration Library
################################################################################
file(GLOB configuration_SRC
    "*.cpp"
)
list(SORT configuration_SRC)

add_library(configuration SHARED ${configuration_SRC})
set_target_properties (configuration PROPERTIES VERSION ${SM_VERSION} SOVERSION ${SM_MAJOR_VERSION})

target_link_libraries(configuration common_header)
install(TARGETS configuration LIBRARY DESTINATION lib)
