#include <stdio.h> 
#include <math.h> 
int main(void) {
    int sumsOfThreeDigits[28];
    for (int i = 0; i <= 27; ++i) {
        sumsOfThreeDigits[i] = 0;
    }
    for (int digit1 = 0; digit1 <= 9; ++digit1) {
        for (int digit2 = 0; digit2 <= 9; ++digit2) {
            for (int digit3 = 0; digit3 <= 9; ++digit3) {
                int digitSum = digit1 + digit2 + digit3;
                sumsOfThreeDigits[digitSum] += 1;
            }
        }
    }
    int ticketsCounter = 0;
    for (int j = 0; j <= 27; ++j) {
        ticketsCounter += pow(sumsOfThreeDigits[j], 2);
    }
    printf("%d", ticketsCounter);
}