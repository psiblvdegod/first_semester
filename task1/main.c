#include <stdio.h>
#include "test.h"
#include "binaryConversion.h"


int main(void) {
    if (!conversionTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    bool errorCode = false;
    const char *string = "10011011";
    const long decimal = convertToDecimal(string, &errorCode);
    if (errorCode) {
        printf("Something went wrong.\n");
        return -1;
    }
    printf("dec: %ld\n", decimal);
}
