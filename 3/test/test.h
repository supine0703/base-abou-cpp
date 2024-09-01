#ifndef LZL_TEST_H
#define LZL_TEST_H

namespace lzl
{

class Test
{
public:
    Test() = default;
    Test(int argc, const char* argv[]) : Test() {}

    int operator()();

private:

    void test_hello();

    void test_pair();
};

} // namespace lzl

#endif // LZL_TEST_H
