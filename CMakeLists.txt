cmake_minimum_required(VERSION 3.8)

project(snake)

set(CMAKE_C_FLAGS "${CMAKE_ENABLE_C99}")

include_directories( ${MY_SOURCE_DIR} )

add_executable(snake main.c console.c board.c)