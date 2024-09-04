
## 介绍

- 深入使用类的继承和模板封装库，分别使用数组、链表、块的方式，例如：stack
  - `array_stack`: 数组封装的栈，缺点：扩容拷贝
  - `list_stack`: 纯链表封装的栈，缺点：空间利用率低
  - `stack`: 块(链表+数组)，弥补上述缺点
- 进阶使用脚本编译


## 构建

> 进阶：使用参数和判断条件优化脚本，避免通过文件区分脚本

### windows

build.bat
- 第一个参数：
  - msvc: 使用 `Visual Studio 17 2022` 进行 cmake 编译
  - mingw: 使用 `MinGW Makefiles` 进行 cmake 编译
  - 无：默认使用 `mingw`
- 第二个参数：
  - -ntest: 不编译测试程序（只有第一个参数无时，才能作为第一个参数）

test.bat
- 第一个参数：
  - msvc: 先编译（ `msvc` ）在运行测试程序
  - mingw: 先编译（ `mingw` ）在运行测试程序
  - reb: 仅重新编译测试程序，并运行
  - 无：直接运行测试程序

#### 示例

> 注意：使用 `cmd` 不能加 `./`；使用`powershell` 必须加 `./`

只编译库 使用 msvc
```sh
./build msvc -ntest
```
默认编译（mingw），默认测试
```sh
./build
./test
```
使用 mingw 编译并测试
```sh
./test mingw
```


### linux

需要先给可执行权限再运行脚本
```sh
chomd +x ./build.sh ./test.sh
./build.sh && ./test.sh
```

