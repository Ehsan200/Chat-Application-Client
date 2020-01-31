cmake_minimum_required(VERSION 3.15)
project(succesfulchat C)

set(CMAKE_C_STANDARD 99)

add_executable(succesfulchat main.c cJSON.c cJSON.h)

target_link_libraries(succesfulchat ws2_32)