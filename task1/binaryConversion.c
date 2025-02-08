#include "binaryConversion.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

long convertToDecimal(const char *string, bool *errorCode) {
    if (string == NULL) {
        *errorCode = true;
        return -1;
    }
    const int length = (int)strlen(string);
    if (length == 0) {
        *errorCode = true;
        return -1;
    }
    long sum = 0;
    for (long i = 0, exp = length - 1; i < length; ++i, --exp) {
        if (string[i] == '1') {
            sum += (int)pow(2, exp);
        }
    }
    return sum;
}