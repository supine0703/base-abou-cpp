
#include "en/hello_en.h"
#include "zh/hello_zh.h"

#include <iostream>

void lzl::hello::en()
{
    std::cout << "Hello, world!" << std::endl;
}

void lzl::hello::zh()
{
    std::cout << "你好，世界!" << std::endl;
}
