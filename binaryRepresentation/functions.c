#include <math.h>
#include <stdlib.h>
#define REGISTER_WIDTH 16

int *bin(int decimal) {
    if (decimal < 0) {
        decimal = pow(2, REGISTER_WIDTH) + decimal;
    }
    int *binary = (int *)calloc(REGISTER_WIDTH, sizeof(int));
    for (int i = 1; i <= REGISTER_WIDTH; ++i) {
        binary[REGISTER_WIDTH - i] = decimal % 2;
        decimal /= 2;
    }
    return binary;
}

int *binSum(int *binary1, int *binary2) {
    for (int i = REGISTER_WIDTH - 1; i >= 0; --i) {
        binary1[i] += binary2[i];
        if (binary1[i] > 1) {
            binary1[i] -= 2;
            ++binary1[i - 1];
        }
    }
    return binary1;
}

int dec(int *binary) {
    int sign = 1;
    if (binary[0]) {
        sign = -1;
        for (int i = 0; i < REGISTER_WIDTH; ++i) {
            binary[i] = binary[i] ? 0 : 1;
        }
        binary = binSum(binary, bin(1));
    }
    int result = 0;
    for (int i = 0; i < REGISTER_WIDTH; ++i) {
        result += binary[REGISTER_WIDTH - i - 1] * pow(2, i);
    }
    return result * sign;
}
