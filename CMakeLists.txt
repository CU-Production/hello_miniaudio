cmake_minimum_required(VERSION 3.25)
project(miniaudio)

set(CMAKE_CXX_STANDARD 20)

add_executable(miniaudio-high-level-api hello-ma-highlevelAPI.cpp)
add_executable(miniaudio-low-level-api hello-ma-lowlevelAPI.cpp)
add_executable(miniaudio-sinewave hello-ma-sinewave.cpp)
