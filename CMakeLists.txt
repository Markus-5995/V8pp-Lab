cmake_minimum_required(VERSION 3.15)
project(V8ppLab CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_EXAMPLE ON)

find_package(v8pp REQUIRED)
find_package(V8 REQUIRED)

add_subdirectory(appconcepts)
add_subdirectory(jsprovider)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()


add_library(V8ppLab SHARED
    include/v8pp-lab/runner.hpp
    include/v8pp-lab/v8ppenvironment.hpp
    src/runner.cpp
    src/v8ppenvironment.cpp
)

target_include_directories(V8ppLab
    PUBLIC
    include)

target_link_libraries(V8ppLab
    PUBLIC
    JSProvider)

