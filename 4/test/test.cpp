#include "test.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;

// #define __LZL_TEST 1

int lzl::Test::operator()()
{
    cout << "\n########################################"
         << "\n########     ! Test start !     ########"
         << "\n########################################\n"
         << endl;
    test_hello();
    test_pair();
    test_array_stack();
    test_array_deque();
    test_array_stack_and_array_deque();
    test_list_stack();
    test_list_queue();
    test_list_deque();
    test_stack();
    test_queue();
    test_deque();
    test_other();
    cout << "\n########################################"
         << "\n########     !  Test end  !     ########"
         << "\n########################################\n"
         << endl;
    return 0;
}

#include "lzl/hello/lzl.h"
#include "lzl/hello/world.h"
void lzl::Test::test_hello()
{
    lzl::hello::world_zh();
    lzl::hello::world_en();
    lzl::hello::lzl();
    cout << endl;
}

#include "lzl/pair"
void lzl::Test::test_pair()
{
    cout << "###########  Test lzl::pair:  ##########\n\n";

    lzl::pair<int, char> p1('1', '2');
    lzl::pair<const char*, int> p2("54321", 5);
    lzl::pair<std::string, int> p3("", 0);
    cout << "p1<int, char>: \t\t(" << p1.first << ", " << p1.second << ")\n";
    cout << "p2<const char*, int>: \t(" << p2.first << ", " << p2.second << ")\n";
    cout << "p3<std::string, int>: \t(" << p3.first << ", " << p3.second << ")\n";

    // p1 = p2; p1 = p3; // cannot compile
    // p2 = p1; p2 = p3; // cannot compile
    cout << "\ncannot compile: [p1 = p2, p1 = p3], [p2 = p1, p2 = p3]\n";

    p3 = p1;
    cout << "\np3 = p1, p3: (" << p3.first << ", " << p3.second << ")\n";
    p3 = p2;
    cout << "p3 = p2, p3: (" << p3.first << ", " << p3.second << ")\n";

    lzl::pair<unsigned int, unsigned int> p4 = lzl::make_pair(-1, size_t(-2));
    auto [a, b] = p4;
    cout << "\n[a, b] = p4<uint, uint>: (" << p4.first << ", " << p4.second << ")\n";
    p4.swap(p1);
    cout << "p4.swap(p1), \tp4: (" << p4.first << ",      " << p4.second << ")\n";
    cout << "             \tp1: (" << p1.first << ", (int)" << (int)p1.second << ")\n";

    // p1.swap(p2); p1.swap(p3); p2.swap(p3); p2.swap(p4); p3.swap(p4); // cannot compile
    cout << "cannot compile: [p1.swap(p2), p1.swap(p3), p2.swap(p3), p2.swap(p4), p3.swap(p4)]\n";

    cout << endl;
}

#include "lzl/array_stack"
void lzl::Test::test_array_stack()
{
    cout << "#######  Test lzl::array_stack:  #######\n\n";

    lzl::array_stack<int> stack(2);
    stack.push(1);
    stack.push(2);
    cout << "capacity: 2, push: [1, 2]\n";
    cout << "size: " << stack.size() << " top: " << stack.top() << '\n';

    stack.reserve(4);
    cout << "reserve: 4\ncapacity: " << stack.capacity() << " size: " << stack.size()
         << " top: " << stack.top() << '\n';

    auto s = stack;
    stack.pop();
    stack.shrink_to_fit();
    cout << "pop, shrink_to_fit\ncapacity: " << stack.capacity() << " size: " << stack.size()
         << " top: " << stack.top() << '\n';

    stack.top() = 3;
    cout << "[3] != [1, 2]: " << (stack != s) << '\n';
    cout << "[3] < [1, 2]: " << (stack < s) << '\n';

    cout << endl;
}

#include "lzl/array_deque"
void lzl::Test::test_array_deque()
{
    cout << "#######  Test lzl::array_deque:  #######\n\n";

    lzl::array_deque<int> deque(2);
    deque.push_back(2);
    deque.push_front(1);
    cout << "capacity: 2, push_back: [2], push_front: [1]\n";
    cout << "size: " << deque.size() << " front: " << deque.front() << " back: " << deque.back()
         << '\n';

    deque.reserve(4);
    cout << "reserve: 4\ncapacity: " << deque.capacity() << " size: " << deque.size()
         << " front: " << deque.front() << " back: " << deque.back() << '\n';

    auto d = deque;
    deque.push_back(3);
    deque.pop_back();
    deque.pop_front();
    deque.shrink_to_fit();
    cout << "push_back: [3], pop_back, pop_front, shrink_to_fit\ncapacity: " << deque.capacity()
         << " size: " << deque.size() << " front: " << deque.front() << " back: " << deque.back()
         << '\n';

    d.pop_back();
    cout << "[2] != [1]: " << (deque != d) << '\n';
    cout << "[2] > [1]: " << (deque > d) << '\n';

    cout << endl;
}

void lzl::Test::test_array_stack_and_array_deque()
{
    cout << "####  array_stack and array_deque:  ####\n\n";

    lzl::array_stack<int> stack(2);
    lzl::array_deque<int> deque(3);
    stack.push(2);
    deque.push_front(4);
    deque.push_front(3);
    deque.push_back(5);
    cout << "array_stack: capacity: 2, push: [2]\n"
         << "array_deque: capacity: 3, push_front: [4, 3], push_back: [5]\n";

    // lzl::array_stack<int> s = deque; // cannot compile
    // lzl::array_deque<int> d = stack; // cannot compile
    cout << "cannot compile: array_stack = deque or array_deque = stack\n";

    // stack.swap(deque); // cannot compile
    // deque.swap(stack); // cannot compile
    cout << "cannot compile: stack.swap(deque) or deque.swap(stack)\n";

    stack.assign(deque);
    cout << "stack.assign(deque):\nstack.size: " << stack.size() << " stack.top: " << stack.top()
         << '\n';

    stack.clear();
    stack.reserve(4);
    stack.push(6);
    stack.push(7);
    stack.push(8);
    stack.push(9);
    deque.assign(stack);
    cout << "stack.clear, stack.reserve: 3, stack.push: [6, 7, 8, 9]\n"
         << "deque.assign(stack):\ndeque.size: " << deque.size()
         << " deque.front: " << deque.front() << " deque.back: " << deque.back() << '\n';

    cout << endl;
}

#include "lzl/list_stack"
void lzl::Test::test_list_stack()
{
    cout << "########  Test lzl::list_stack:  #######\n\n";

    lzl::list_stack<int> stack;
    stack.push(1);
    stack.push(2);
    cout << "push: [1, 2]\n";
    cout << "size: " << stack.size() << " top: " << stack.top() << '\n';

    stack.push(3);
    stack.push(4);
    cout << "push: [3, 4]\n";
    cout << "size: " << stack.size() << " top: " << stack.top() << '\n';

    stack.pop();
    stack.pop();
    stack.pop();
    cout << "pop: 3 times\n";
    cout << "size: " << stack.size() << " top: " << stack.top() << '\n';

    lzl::list_stack<int> s;
    s.push(1);
    s.push(2);
    stack.top() = 3;
    cout << "[3] != [1, 2]: " << (stack != s) << '\n';
    cout << "[3] < [1, 2]: " << (stack < s) << '\n';

    cout << endl;
}

#include "lzl/list_queue"
void lzl::Test::test_list_queue()
{
    cout << "########  Test lzl::list_queue:  #######\n\n";

    lzl::list_queue<int> queue;
    queue.push(1);
    queue.push(2);
    cout << "push: [1, 2]\n";
    cout << "size: " << queue.size() << " font: " << queue.front() << " back: " << queue.back()
         << '\n';

    queue.push(3);
    queue.push(4);
    cout << "push: [3, 4]\n";
    cout << "size: " << queue.size() << " font: " << queue.front() << " back: " << queue.back()
         << '\n';

    queue.pop();
    queue.pop();
    queue.pop();
    cout << "pop: 3 times\n";
    cout << "size: " << queue.size() << " font: " << queue.front() << " back: " << queue.back()
         << '\n';

    lzl::list_queue<int> q;
    q.push(3);
    cout << "[4] != [3]: " << (queue != q) << '\n';
    cout << "[4] > [3]: " << (queue > q) << '\n';

    cout << endl;
}

#include "lzl/list_deque"
void lzl::Test::test_list_deque()
{
    cout << "########  Test lzl::list_deque:  #######\n\n";

    lzl::list_deque<int> deque;
    deque.push_back(1);
    deque.push_back(2);
    cout << "push_back: [1, 2]\n";
    cout << "size: " << deque.size() << " front: " << deque.front() << " back: " << deque.back()
         << '\n';

    deque.push_front(3);
    deque.push_front(4);
    cout << "push_front: [3, 4]\n";
    cout << "size: " << deque.size() << " front: " << deque.front() << " back: " << deque.back()
         << '\n';

    deque.pop_back();
    cout << "pop_back\n";
    cout << "size: " << deque.size() << " front: " << deque.front() << " back: " << deque.back()
         << '\n';

    deque.pop_front();
    cout << "pop_front\n";
    cout << "size: " << deque.size() << " front: " << deque.front() << " back: " << deque.back()
         << '\n';

    lzl::list_deque<int> d;
    d.push_back(3);
    d.push_back(1);
    cout << "[3, 1] <= [3, 1]: " << (deque != d) << '\n';
    cout << "[3, 1] < [3, 1]: " << (deque < d) << '\n';

    cout << endl;
}

#include "lzl/stack"
void lzl::Test::test_stack()
{
    cout << "##########  Test lzl::stack:  ##########\n\n";

    lzl::stack<int, char, 8> s;
    // cout << "array_unit_size: " << s.array_unit_size() << '\n';
    s.push(1);
    s.push(2);
    cout << "push: [1, 2]\n";
    cout << "size: " << s.size() << " top: " << s.top() << '\n';

    s.push(3);
    s.push(4);
    cout << "push: [3, 4]\n";
    cout << "size: " << s.size() << " top: " << s.top() << '\n';

    s.pop();
    s.pop();
    s.pop();
    cout << "pop: 3 times\n";
    cout << "size: " << s.size() << " top: " << s.top() << '\n';

    lzl::stack<int, char, 8> ss;
    ss.push(1);
    ss.push(2);
    s.push(3);
    cout << "[1, 3] != [1, 2]: " << (s != ss) << '\n';
    cout << "[1, 3] < [1, 2]: " << (s < ss) << '\n';

    cout << endl;
}

#include "lzl/queue"
void lzl::Test::test_queue()
{
    cout << "##########  Test lzl::queue:  ##########\n\n";

    lzl::queue<int, char, 8> q;
    // cout << "array_unit_size: " << s.array_unit_size() << '\n';
    q.push(1);
    q.push(2);
    cout << "push: [1, 2]\n";
    cout << "size: " << q.size() << " font: " << q.front() << " back: " << q.back() << '\n';

    q.push(3);
    q.push(4);
    cout << "push: [3, 4]\n";
    cout << "size: " << q.size() << " font: " << q.front() << " back: " << q.back() << '\n';

    q.pop();
    q.pop();
    q.pop();
    cout << "pop: 3 times\n";
    cout << "size: " << q.size() << " font: " << q.front() << " back: " << q.back() << '\n';

    lzl::queue<int, char, 8> qq;
    qq.push(1);
    qq.push(2);
    q.push(3);
    q.front() = 1;
    q.back() = 2;
    cout << "[1, 2] != [2, 1]: " << (q != qq) << '\n';
    cout << "[1, 2] < [2, 1]: " << (q < qq) << '\n';

    cout << endl;
}

#include "lzl/deque"
void lzl::Test::test_deque()
{
    cout << "##########  Test lzl::deque:  ##########\n\n";

    lzl::deque<int, char, 8> d;
    cout << "array_unit_size: " << d.array_unit_size() << '\n';
    d.push_front(1);
    d.push_front(2);
    cout << "push_front: [1, 2]\n";
    cout << "size: " << d.size() << " front: " << d.front() << " back: " << d.back() << '\n';

    d.push_back(3);
    d.push_back(4);
    cout << "push_back: [3, 4]\n";
    cout << "size: " << d.size() << " front: " << d.front() << " back: " << d.back() << '\n';

    d.pop_back();
    cout << "pop_back\n";
    cout << "size: " << d.size() << " front: " << d.front() << " back: " << d.back() << '\n';

    d.pop_front();
    cout << "pop_front\n";
    cout << "size: " << d.size() << " front: " << d.front() << " back: " << d.back() << '\n';

    lzl::deque<int, char, 8> dd;
    dd.push_front(1);
    dd.push_back(3);
    dd.push_back(4);
    d.push_back(4);
    cout << "[1, 3, 4] == [1, 3, 4]: " << (d == dd) << '\n';

    d.back() = 2;
    cout << "[1, 3, 2] < [1, 3, 4]: " << (d < dd) << '\n';

    dd.pop_front();
    cout << "[1, 3, 2] <= [3, 4]: " << (d <= dd) << '\n'; 

    cout << endl;
}

void lzl::Test::test_other()
{
    // lzl::array_stack<int> s1(3);
    // s1.push(1);
    // s1.push(2);
    // lzl::array_stack<int> s2(4);
    // s2.push(3);

    // cout << "[1, 2] < [3]: " << (s1 < s2) << '\n';
    // cout << "[1, 2] <= [3]: " << (s1 <= s2) << '\n';
    // cout << "[1, 2] == [3]: " << (s1 == s2) << '\n';
    // cout << "[1, 2] != [3]: " << (s1 != s2) << '\n';
    // cout << "[1, 2] >= [3]: " << (s1 >= s2) << '\n';
    // cout << "[1, 2] > [3]: " << (s1 > s2) << '\n';

    // s2.push(4);
    // cout << "[1, 2] < [3, 4]: " << (s1 < s2) << '\n';
    // cout << "[1, 2] <= [3, 4]: " << (s1 <= s2) << '\n';
    // cout << "[1, 2] == [3, 4]: " << (s1 == s2) << '\n';
    // cout << "[1, 2] != [3, 4]: " << (s1 != s2) << '\n';
    // cout << "[1, 2] >= [3, 4]: " << (s1 >= s2) << '\n';
    // cout << "[1, 2] > [3, 4]: " << (s1 > s2) << '\n';

    // lzl::array_deque<int> d1(3);
    // d1.push_back(1);
    // d1.push_back(2);
    // lzl::array_deque<int> d2(1);
    // d2.push_front(2);
    // d2.reserve(2);
    // d2.push_front(1);

    // cout << "b[1, 2] < f[1, 2]: " << (d1 < d2) << '\n';
    // cout << "b[1, 2] <= f[1, 2]: " << (d1 <= d2) << '\n';
    // cout << "b[1, 2] == f[1, 2]: " << (d1 == d2) << '\n';
    // cout << "b[1, 2] != f[1, 2]: " << (d1 != d2) << '\n';
    // cout << "b[1, 2] >= f[1, 2]: " << (d1 >= d2) << '\n';
    // cout << "b[1, 2] > f[1, 2]: " << (d1 > d2) << '\n';
}
