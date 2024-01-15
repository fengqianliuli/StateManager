################################################################################
# Class Loader library
################################################################################
file(GLOB shared_library_SRC
    "*.cpp"
)
list(SORT shared_library_SRC)

add_library(shared_library SHARED ${shared_library_SRC})
set_target_properties (shared_library PROPERTIES VERSION ${SM_VERSION} SOVERSION ${SM_MAJOR_VERSION})

target_include_directories(shared_library INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(shared_library ${DL_LIBRARY})
