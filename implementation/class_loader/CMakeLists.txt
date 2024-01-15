add_subdirectory(shared_library)
add_subdirectory(utility)

################################################################################
# Class Loader Manager library
################################################################################
file(GLOB class_loader_manager_SRC
    "*.cpp"
)
list(SORT class_loader_manager_SRC)

add_library(class_loader_manager SHARED ${class_loader_manager_SRC})
set_target_properties (class_loader_manager PROPERTIES VERSION ${SM_VERSION} SOVERSION ${SM_MAJOR_VERSION})

target_include_directories(class_loader_manager INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(class_loader_manager class_loader_utility shared_library common_header)
