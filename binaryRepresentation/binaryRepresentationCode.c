#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#define REGISTER_WIDTH 16

int *bin(int decimal) {
    if (decimal < 0) {
        decimal = pow(2, REGISTER_WIDTH) + decimal;
    }
    int *binary = malloc(sizeof(int) * REGISTER_WIDTH);
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

bool binTest() {
    int *bin1 = bin(65000), *bin2 = bin(535);
    int *bin3 = bin(10000), *bin4 = bin(-10000);
    int *binSum1 = binSum(bin1, bin2);
    int *binSum2 = binSum(bin3, bin4);
    for (int i = 0; i < REGISTER_WIDTH; ++i) {
        if (binSum1[i] != 1 || binSum2[i] != 0) {
            return false;
        }
    }
    return true;
}

int dec(int *binary) {
    int result = 0;
    int sign = 1;
    if (binary[0]) {
        sign = -1;
        for (int i = 0; i < REGISTER_WIDTH; ++i) {
            binary[i] = binary[i] ? 0 : 1;
        }
        binary = binSum(binary, bin(1));
    }
    for (int i = 0; i < REGISTER_WIDTH; ++i) {
        result += binary[REGISTER_WIDTH - i - 1] * pow(2, i);
    }
    return result * sign;
}

bool decTest() {
    int *binary1 = bin(5);
    int *binary2 = bin(-5);
    return (dec(binary1) == 5 && dec(binary2) == -5);
}

int main(void) {
    if (!decTest() || !binTest()) {
        return -1;
    }
}