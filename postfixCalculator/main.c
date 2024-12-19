#include "tests.h"
#include <stdio.h>

int main(void) {
    if (!stackTest() || !calculatorTest()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
}