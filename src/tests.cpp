#include "test_utils.h"

void runTests()
{
    int n = 1;
    expect("little endian", *(char *)&n, 1);
}

int main()
{
    runTests();

    return 0;
}