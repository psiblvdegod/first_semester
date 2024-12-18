#include "binaryConversion.h"
#include <string.h>
#include <math.h>

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
    long result = 0;
    for (long i = 0, exp = length - 1; i < length; ++i, --exp) {
        if (string[i] == '1') {
            result += (int)pow(2, exp);
        }
    }
    return result;
}