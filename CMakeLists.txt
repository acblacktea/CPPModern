cmake_minimum_required(VERSION 3.26)
project(ModernCPP)

set(CMAKE_CXX_STANDARD 23)

add_executable(ModernCPP main.cpp
        useability/useability.cpp
        runtime/runtime.cpp
        container/container.cpp
        pointer/pointer.cpp
        parallelism/parallelism.cpp)
