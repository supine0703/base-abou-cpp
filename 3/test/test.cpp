#include "test.h"

#include <iostream>
#include <string>

using std::cout;
using std::endl;

int lzl::Test::operator()()
{
    cout << "\n########################################"
         << "\n########     ! Test start !     ########"
         << "\n########################################\n"
         << endl;
    test_hello();
    test_pair();
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
    cout << "#############  Test lzl::pair:  #############\n\n";

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
