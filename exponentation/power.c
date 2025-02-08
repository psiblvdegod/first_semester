#include <stdlib.h>
#include "power.h"

double powerLinear(const int base, const int exponent) {
    double result = 1.0;
    for (int i = 0; i < abs(exponent); ++ i) {
        result *= base;
    }
    return exponent > 0 ? result : 1.0 / result;
}

double powerLogarithmic(int base, int exponent) {
    double result = 1.0;
    const int exponentSign = exponent >= 0 ? 1 : -1;
    exponent *= exponentSign;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result *= base;
        }
        base *= base;
        exponent /= 2;
    }
    return exponentSign > 0 ? result : 1.0 / result;
}