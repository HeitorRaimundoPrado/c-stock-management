cmake_minimum_required(VERSION 3.9.1)

project(c-stock-manager)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

add_executable(stock_manager src/main.c src/manage.h src/manage.c)

