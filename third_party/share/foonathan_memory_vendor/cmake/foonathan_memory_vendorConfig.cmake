# prevent multiple inclusion
if(_foonathan_memory_vendor_CONFIG_INCLUDED)
  return()
endif()
set(_foonathan_memory_vendor_CONFIG_INCLUDED TRUE)

# output package information
if(NOT foonathan_memory_vendor_FIND_QUIETLY)
  message(STATUS "Found foonathan_memory_vendor: 0.7.1 (${foonathan_memory_vendor_DIR})")
endif()
