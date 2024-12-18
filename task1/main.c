#include <stdio.h>
#include "binaryConvertion.h"


int main(void) {
    bool errorCode = false;
    const char *string = "10011011";
    const long decimal = convertToDecimal(string, &errorCode);
    if (errorCode) {
        printf("Something went wrong.\n");
        return -1;
    }
    printf("dec: %d\n", (int) decimal);
}
