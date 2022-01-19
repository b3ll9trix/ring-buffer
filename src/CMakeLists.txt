cmake_minimum_required(VERSION 3.21)
project(src)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

add_executable(src main.cpp RingBuffer.h Frame.h Exceptions.h)
