#include "binaryConversion.h"
#include <string.h>
#include <math.h>
#include <stdio.h>

const char *convertToDecimal(const char *string, bool *errorCode) {
    if (string == NULL) {
        *errorCode = true;
        return NULL;
    }
    const int length = (int)strlen(string);
    if (length == 0) {
        *errorCode = true;
        return NULL;
    }
    long sum = 0;
    for (long i = 0, exp = length - 1; i < length; ++i, --exp) {
        if (string[i] == '1') {
            sum += (int)pow(2, exp);
        }
    }
}