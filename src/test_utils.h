#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <iostream>
#include <string>

using namespace std;

// Basic testing helper:
template <typename T, typename K>
void expect(string name, T lhs, K rhs)
{
    lhs == rhs ? cout << "\033[32m" << name << ":\tpassed!\n" : cout << "\033[31m" << name << ":\tfailed...\n\texpected: " << rhs << "\n\treceived: " << lhs << "\n";
    cout << "\033[0m";
}

#endif // TEST_UTILS_H