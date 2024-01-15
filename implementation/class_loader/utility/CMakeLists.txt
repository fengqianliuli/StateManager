################################################################################
# Class Loader library
################################################################################
file(GLOB class_loader_utility_SRC
    "*.cpp"
)
list(SORT class_loader_utility_SRC)

add_library(class_loader_utility SHARED ${class_loader_utility_SRC})
set_target_properties (class_loader_utility PROPERTIES VERSION ${SM_VERSION} SOVERSION ${SM_MAJOR_VERSION})

target_include_directories(class_loader_utility INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(class_loader_utility shared_library)
