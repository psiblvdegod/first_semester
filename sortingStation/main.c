#include <stdio.h>
#include "tests.h"

int main(void) {
    if (!stackTest() || !queueTest() || !sortingStationTest()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
}
