# ...

set(HEADERS
  zh/hello_zh.h
  en/hello_en.h
  Hello
)

set(SOURCES
  hello.cpp
)

# 生成静态库
add_library(lzl-static STATIC ${SOURCES})
set_target_properties(lzl-static PROPERTIES OUTPUT_NAME "lzl_hello")

# 生成动态库
add_library(lzl-shared SHARED ${SOURCES})
set_target_properties(lzl-shared PROPERTIES OUTPUT_NAME "lzl_hello")

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
install(FILES Hello DESTINATION include/lzl)
install(FILES zh/hello_zh.h DESTINATION include/lzl/zh)
install(FILES en/hello_en.h DESTINATION include/lzl/en)
