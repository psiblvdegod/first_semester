#include "test.h"

bool conversionTest() {
    bool errorCode = false;
    const char *string1 = "101";
    const char *string2 = "10000";
    const char *string3 = "11111111";
    const bool test1 = convertToDecimal(string1, &errorCode) == 5;
    const bool test2 = convertToDecimal(string2, &errorCode) == 16;
    const bool test3 = convertToDecimal(string3, &errorCode) == 255;
    return test1 && test2 && test3 && !errorCode;
}