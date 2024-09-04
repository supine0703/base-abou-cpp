#include "hello.h"

#include <cstdarg>
#include <iostream>

void lzl::hello::zh(const char* format, ...)
{
    printf("你好，");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf(" —— 来自李宗霖\n");
}

void lzl::hello::en(const char* format, ...)
{
    printf("Hello, ");
    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("  -- from lzl\n");
}


#include "world.h"

void lzl::hello::world_zh()
{
    zh("世界！");
}

void lzl::hello::world_en()
{
    en("World!");
}


#include "lzl.h"

void lzl::hello::lzl()
{
    std::cout << R"( _____   __   __  __ _     _____ _)" << '\n'
              << R"(|_   _| /  \ |  \/  | |   |___  | |)" << '\n'
              << R"(  | |  / /\ \| \  / | |      / /| |)" << '\n'
              << R"(  | | | |__| | |\/| | |     / / | |)" << '\n'
              << R"( _| |_|  __  | |  | | |___ / /__| |___)" << '\n'
              << R"(|_____|_|  |_|_|  |_|_____|_____|_____|)" << std::endl;
}
