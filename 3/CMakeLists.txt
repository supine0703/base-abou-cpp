cmake_minimum_required(VERSION 3.15)

project(Demo VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/install)

if(WIN32)
  set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON) # 生成DLL时需要导出所有符号

  # 设置编译选项，为了在Windows下能够正确显示中文
  if(MSVC)
    string(APPEND CMAKE_CXX_FLAGS " /source-charset:utf-8 /execution-charset:GBK")
  elseif(CMAKE_COMPILER_IS_GNUCXX)
    string(APPEND CMAKE_CXX_FLAGS " -fexec-charset=GBK")
  endif()

elseif(UNIX)
  # 为了在Linux下能够正确加载动态库，需要设置RPATH
  set(CMAKE_SKIP_BUILD_RPATH TRUE)
  string(APPEND CMAKE_CXX_FLAGS "-Wl,-z,origin,-rpath,'$ORIGIN'")
endif()

# 构建项目
add_subdirectory(src)

# 定义选项
option(BUILD_TEST "build test program" OFF)

# 根据 MAKE_TEST 的值决定是否构建 test
if(NOT BUILD_TEST)
  message(STATUS "Not build test program")
else()
  add_subdirectory(test)
  message(STATUS "Build test program")
endif()
