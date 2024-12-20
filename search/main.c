#include "tests.h"

int main(void) {
    if (!smartQsortTest() || !insertionSortTest()) {
        return -1;
    }
}