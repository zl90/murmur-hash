#include "test_utils.h"
#include "murmur.h"

void runTests()
{
    int n = 1;
    expect("little endian", *(char *)&n, 1);
    expect("test1", murmur3_32("abcde", 123), 3346734134);
}

int main()
{
    runTests();

    return 0;
}