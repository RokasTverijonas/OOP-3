cmake_minimum_required(VERSION 3.10)
project(OOP-2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP true
)
FetchContent_MakeAvailable(googletest)

include_directories(include/)

file(GLOB TXT_FILES "${CMAKE_SOURCE_DIR}/*.txt")
file(COPY ${TXT_FILES} DESTINATION ${CMAKE_BINARY_DIR})

add_executable(programa1
    src/main.cpp
    src/funkcijos.cpp
)

add_executable(gtestai
    tests/testai.cpp
    src/funkcijos.cpp
)
add_executable(vecTestai
    tests/vectorTests.cpp
)

target_link_libraries(gtestai gtest gtest_main)
target_link_libraries(vecTestai gtest gtest_main)