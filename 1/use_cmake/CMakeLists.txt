cmake_minimum_required(VERSION 3.5.0)

project(hello VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=GBK")
endif()

include_directories(src)

file(GLOB_RECURSE SOURCES src/*.cpp)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    main.cpp
)
