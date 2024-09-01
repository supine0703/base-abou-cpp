
set(PROJ_INCLUDE_PATH ${CMAKE_INSTALL_PREFIX}/include)
set(STATIC_LIB_PATH ${CMAKE_INSTALL_PREFIX}/static)
set(SHARED_LIB_PATH ${CMAKE_INSTALL_PREFIX}/shared)

set(PROJECT_SOURCES
    main.cpp
)

include_directories(${PROJ_INCLUDE_PATH})

# 链接静态库 并 生成测试用的可执行文件
find_library(STATIC_LIB lzl_hello ${STATIC_LIB_PATH})
add_executable(static_test ${PROJECT_SOURCES})
target_link_libraries(static_test PRIVATE ${STATIC_LIB})

# 链接动态库 并 生成测试用的可执行文件
find_library(SHARED_LIB lzl_hello ${SHARED_LIB_PATH})
add_executable(shared_test ${PROJECT_SOURCES})
target_link_libraries(shared_test PRIVATE ${SHARED_LIB})

# 安装测试用的可执行文件和动态库文件
set(TEST_PATH test)
install(TARGETS static_test RUNTIME DESTINATION ${TEST_PATH})
install(TARGETS shared_test RUNTIME DESTINATION ${TEST_PATH})

file(GLOB SHARED_LIB_FILES ${SHARED_LIB_PATH}/*.so ${SHARED_LIB_PATH}/*.dll)
install(FILES ${SHARED_LIB_FILES} DESTINATION ${TEST_PATH})

