#include <stdio.h> 
#include <stdbool.h> 

int primeNumbers(int *inputInteger) {
    for (int i = 2; i <= inputInteger; ++i) {
        bool checkPrimeStatus = true;
        for (int k = 2; k < i; ++k) {
            if (i % k == 0) {
                checkPrimeStatus = false;
                break;
            }
        }
        if (checkPrimeStatus == true) {
            printf("%d ", i);
        }
    }
}

int main(void) {
    int inputInteger = 1;
    printf("Enter the number.\n");
    scanf("%d", &inputInteger);
    primeNumbers(inputInteger);
}