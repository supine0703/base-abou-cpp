# ...

include_directories(lib)

file(GLOB LZL_HELLO_HEADERS hello/*.h)
file(GLOB LZL_LIB_AND_INC_HEADERS lib/*.h inc/*)

set(LZL_HEADERS
  ${LZL_LIB_AND_INC_HEADERS}
)

set(SOURCES
  hello/hello.cpp
)

# 生成静态库
add_library(lzl-static STATIC ${SOURCES})
set_target_properties(lzl-static PROPERTIES OUTPUT_NAME "lzl_pair")

# 生成动态库
add_library(lzl-shared SHARED ${SOURCES})
set_target_properties(lzl-shared PROPERTIES OUTPUT_NAME "lzl_pair")

# 安装静态库
set(STATIC_PATH static)
install(TARGETS lzl-static
  ARCHIVE DESTINATION ${STATIC_PATH}
)

# 安装动态库
set(SHARED_PATH shared)
install(TARGETS lzl-shared
  LIBRARY DESTINATION ${SHARED_PATH}
  ARCHIVE DESTINATION ${SHARED_PATH}
  RUNTIME DESTINATION ${SHARED_PATH}
)

# 安装头文件
install(FILES ${LZL_HEADERS} DESTINATION include/lzl)
install(FILES ${LZL_HELLO_HEADERS} DESTINATION include/lzl/hello)

