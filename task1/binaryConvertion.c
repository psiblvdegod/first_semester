#include "binaryConvertion.h"
#include <string.h>
#include <math.h>

long convertToDecimal(const char *string, bool *errorCode) {
    const int length = (int)strlen(string);
    int result = 0;
    for (long i = 0, exp = length - 1; i < length; ++i, --exp) {
        if (string[i] == '1') {
            result += (int)pow(2, exp);
        }
    }
    return result;
}