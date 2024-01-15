#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "vsomeip3" for configuration "RelWithDebInfo"
set_property(TARGET vsomeip3 APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(vsomeip3 PROPERTIES
  IMPORTED_LINK_DEPENDENT_LIBRARIES_RELWITHDEBINFO "Boost::system;Boost::thread;Boost::filesystem"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/libvsomeip3.so.3.4.10"
  IMPORTED_SONAME_RELWITHDEBINFO "libvsomeip3.so.3"
  )

list(APPEND _cmake_import_check_targets vsomeip3 )
list(APPEND _cmake_import_check_files_for_vsomeip3 "${_IMPORT_PREFIX}/lib/libvsomeip3.so.3.4.10" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
