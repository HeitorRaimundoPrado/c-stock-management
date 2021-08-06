cmake_minimum_required(VERSION 3.9.1)

project(c-stock-manager)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wextra -Wpedantic")

else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O2")

endif()

add_executable(stock_manager src/main.c src/manage.h src/manage.c src/csmconfig.h src/csmconfig.c)

