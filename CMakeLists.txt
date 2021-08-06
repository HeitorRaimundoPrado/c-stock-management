cmake_minimum_required(VERSION 3.9.1)

project(c-stock-manager)

set(CMAKE_C_STANDARD 11)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

if (CMAKE_BUILD_TYPE STREQUAL "")
  add_definitions(-DC_STOCK_MANAGER_BUILD_TYPE="Release")

else()
  add_definitions(-DC_STOCK_MANAGER_BUILD_TYPE="${CMAKE_BUILD_TYPE}")
  add_definitions(-DLOG_FILE_PATH="${EXECUTABLE_OUTPUT_PATH}/log/debug.log")

endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Wpedantic")

else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")

endif()

include_directories(${CMAKE_BINARY_DIR}/src)
add_executable(stock_manager src/main.c src/log.c src/manage.c src/csmconfig.c)

