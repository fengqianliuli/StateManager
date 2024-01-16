cmake_minimum_required(VERSION 3.13)
project(state_manager)

set (SM_MAJOR_VERSION 0)
set (SM_MINOR_VERSION 0)
set (SM_PATCH_VERSION 1)
set (SM_HOTFIX_VERSION 0)

set (SM_VERSION ${SM_MAJOR_VERSION}.${SM_MINOR_VERSION}.${SM_PATCH_VERSION})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

set(CMAKE_INSTALL_PREFIX "./install")
set(CONFIG_DIR "${CMAKE_SOURCE_DIR}/config")

set(USE_RT "rt")
set(DL_LIBRARY "dl")
set(PTHREAD_LIBRARY "pthread")

set(CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/third_party")
find_package(glog REQUIRED)
find_package(nlohmann_json REQUIRED)

add_subdirectory(implementation)



