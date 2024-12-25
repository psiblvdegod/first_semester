#include "tests.h"

int main(void) {
    int errorCode = 0;
    mergeTest(&errorCode);
    mergeSortTest(&errorCode);
    return errorCode;
}