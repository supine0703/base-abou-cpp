cmake_minimum_required(VERSION 3.15.0)

project(Demo VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=GBK")
endif()

file(GLOB SOURCES
    ./base/*.cpp
    ./array/*.cpp
    ./list/*.cpp
)

add_executable(${PROJECT_NAME}
    # list/list.cpp
    main.cpp
)
