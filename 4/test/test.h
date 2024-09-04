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
    void test_other();

    void test_hello();

    void test_pair();

    void test_array_stack();

    void test_array_deque();

    void test_array_stack_and_array_deque();

    void test_list_stack();

    void test_list_queue();

    void test_list_deque();

    void test_stack();

    void test_queue();

    void test_deque();
};

} // namespace lzl

#endif // LZL_TEST_H
