
## 介绍

- 这里主要是使用 cmake 构建项目生成动态库和静态库，并生成测试使用的可执行文件
- 通过脚本和 cmake 实现跨平台：测试完成在 windows 和 linux 下
- 搭建大部分的 cpp 项目，都可以以此为框架展开


## 构建

### windows

如果使用 `MSVC`, 运行 `build-msvc.bat`, 脚本默认使用的是 `Visual Studio 17 2022`, 如果版本不一样, 自行更改

使用 `MinGW` 则直接运行 `build-mingw.bat`

在命令行中运行 `test.bat` 可查看结果


### linux

需要先给可执行权限再运行脚本
```sh
chomd +x ./build.sh ./test.sh
./build.sh && ./test.sh
```

