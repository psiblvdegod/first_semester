#include <stdio.h>
#include <time.h>
#include "test.h"
#include "power.h"

int main(void) {
    if (!powerTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    printf("Linear time exponentiation.\nExponent - time\n");
    for (int i = 1; i < 10; ++i) {
        const clock_t startTime = clock();
        powerLinear(2, i * 10000000);
        const double duration = (double) (clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d - %lf\n", i * 10000000, duration);
    }
    printf("Logarithmic time exponentiation.\nExponent - time\n");
    for (int i = 1; i < 10; ++i) {
        const clock_t startTime = clock();
        powerLogarithmic(2, i * 10000000);
        const double duration = (double) (clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d - %lf\n", i * 10000000, duration);
    }
}