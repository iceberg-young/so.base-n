cmake_minimum_required(VERSION 3.2)

project(so.base-n)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")
set(SOURCE_FILES
    base16_decode.cpp
    base16_encode.cpp
    base32_decode.cpp
    base32_encode.cpp
    base64_decode.cpp
    base64_encode.cpp
)

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})
include_directories(../include)
