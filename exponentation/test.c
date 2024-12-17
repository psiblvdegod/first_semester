#include "test.h"

bool powerTest() {
    const bool test1 = powerLinear(10, 5) == 100000;
    const bool test2 = powerLinear(2, -5) == 0.03125;
    const bool test3 = powerLogarithmic(10, 10) == 10000000000;
    const bool test4 = powerLogarithmic(2, -10) == 0.0009765625;
    return test1 && test2 && test3 && test4;
}
