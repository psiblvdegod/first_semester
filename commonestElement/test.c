#include "test.h"

bool test() {
    int array[] = { -5, -5, 10, 10, 10, 10, 10, 10, -10, 5, 5, 5, 10, 10 };
    const int arraySize = sizeof(array) / sizeof(int);
    bool errorCode = false;
    return findCommonestElement(array, arraySize, &errorCode) == 10 && !errorCode;
}