#include <stdio.h>
#include "tests.h"

int main(void) {
    if (!hashTableTests()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
}