
### Use gcc

> c 使用 gcc | c++ 使用 g++

够用的参数
- `-o`: 可执行文件名
- `-fexec-charset=`
  - `gbk`: windows 命令行使用 `gbk` 编码
- `-I`: 链接头文件目录

<div class="tree">./use_gcc
├─include
│ └──hello.h
│
├─src
│ └──hello.cpp
│
├──hello.exe
└──main.cpp
</div>

```sh
cd ./use_gcc
g++.exe ./*.cpp ./src/*.cpp -o hello.exe -I ./include/ -fexec-charset=gbk
```

### Use cmake

<div class="tree">./use_cmake
├─build
│ └─...
│
├─src
│ ├──hello.h
│ └──hello.cpp
│
├──CMakeLists.txt
└──main.cpp
</div>

```sh
mkdir build
cd build
cmake -G "MinGW Makefiles" ..
make # or mingw32-make
```

### cmake 语法

#### 基本项目语法模板

```cmake
cmake_minimum_required(VERSION 3.5.0) # 设置 cmake最低版本

project(demo VERSION 0.1.0 LANGUAGES CXX) # 设置项目进本信息

# 下面使用 c++11 ， 其他可自行了解或者就照抄
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# windows 使用 mingw (gcc) 进行编译默认为 utf-8编码，而 windows 是 gbk 编码
if(WIN32 AND CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fexec-charset=GBK")
endif()

# 同 gcc 的 -I 差不多，为了链接头文件路径
include_directories(./include)

# 递归查找 .cpp 文件
file(GLOB_RECURSE SOURCES src/*.cpp)

# 添加生成的可执行文件
add_executable(${PROJECT_NAME}
    ${SOURCES}
    main.cpp
)
```


#### 部分语法简单介绍
- 关于字符串：
  - `${}`: 为解引用
  - 大部分加不加双引号都等价，例如: `${PATH}/a.cpp` 等价于 `"${PATH}/a.cpp"`
  - 若想`关键字`为字符串，则必须加双引号
- `include_directories(...)`: 中间可以加上所有需要 `include` 的路径，用空白符或者`;`分隔，例如：
  - include_directories(./inc1 ./inc2)
- `file([GLOB|GLOB_RECURSE] NAME ...)`:
  - `GLOB`: 寻找目录下所有文件
  - `GLOB_RECURSE`: 递归寻找目录以及子目录下所有文件
  - `NAME`: 存储所有找到文件的路径的变量名
  - `...`: 路径，可使用通配符，空白符或者`;`分隔
- `set(NAME ...)`: 将 `NAME` 定义为变量
-  `add_executable(EXE_NAME ...)`: 
   -  `PROJECT_NAME`: cmake 自带变量，由 `project()` 定义
   -  `EXE_NAME`: 为可执行文件的名字
   -  `...`: 所有 cpp 的路径，不可使用通配符，建议穷举，也可以用 file 查找后解引用



<style>
.tree {
  background-color: rgba(142,168,194,0.08); /* 背景颜色 */
  border: none; /* 边框 */
  border-radius: 4px; /* 圆角 */
  padding: 10px; /* 内边距 */
  margin: 15px 0; /* 外边距 */
  font-family: JetBrains Mono; /* 字体 */
  white-space: pre; /* 保持空格和换行 */
  overflow-x: auto; /* 横向滚动条 */
  line-height: 1.5rem;
}
</style>
