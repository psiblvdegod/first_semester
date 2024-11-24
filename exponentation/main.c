#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

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

bool powerTest() {
    const bool test1 = powerLinear(10, 5) == 100000;
    const bool test2 = powerLinear(2, -5) == 0.03125;
    const bool test3 = powerLogarithmic(10, 10) == 10000000000;
    const bool test4 = powerLogarithmic(2, -10) == 0.0009765625;
    return test1 && test2 && test3 && test4;
}

int main(void) {
    if (!powerTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    printf("Linear time exponentiation.\nExponent - time\n");
    for (int i = 1; i <= 10; ++i) {
        const clock_t startTime = clock();
        powerLinear(2, i * 10000000);
        const double duration = (double) (clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d - %lf\n", i * 10000000, duration);
    }
    printf("Logarithmic time exponentiation.\nExponent - time\n");
    for (int i = 1; i <= 10; ++i) {
        const clock_t startTime = clock();
        powerLogarithmic(2, i * 10000000);
        const double duration = (double) (clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d - %lf\n", i * 10000000, duration);
    }
}