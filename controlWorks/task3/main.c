#include <stdio.h>
#include "test.h"

int main(void) {
    printf("test: ");
    if (!graphTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
}
