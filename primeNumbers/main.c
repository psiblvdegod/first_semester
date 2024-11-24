#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

bool *sieveOfEratosthenes(const int n, bool *errorCode) {
    if (n < 2) {
        return NULL;
    }
    bool *divisibilityArray = calloc(n, sizeof(bool));
    if (divisibilityArray == NULL) {
        *errorCode = true;
        return NULL;
    }
    for (int i = 2; pow(i, 2) <= n; ++i) {
        if (!divisibilityArray[i]) {
            for (int j = (int) pow(i, 2); j <= n; j += i) {
                divisibilityArray[j] = true;
            }
        }
    }
    return divisibilityArray;
}

bool sieveOfEratosthenesArrayTest() {
    bool errorCode = false;
    const int n = 100;
    bool * divisibilityArray = sieveOfEratosthenes(n, &errorCode);
    if (divisibilityArray == NULL || errorCode) {
        free(divisibilityArray);
        return false;
    }
    const bool test1 = !divisibilityArray[11];
    const bool test2 = divisibilityArray[21];
    free(divisibilityArray);
    return test1 && test2 && !errorCode;
}

int main(void) {
    if (!sieveOfEratosthenesArrayTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    int n = 0;
    printf("Enter n.\n");
    if (scanf("%d", &n) != 1) {
        printf("Invalid value.");
        return 1;
    }
    bool errorCode = false;
    bool *divisibilityArray = sieveOfEratosthenes(n, &errorCode);
    if (errorCode) {
        printf("Memory allocation error.\n");
        return -1;
    }
    if (divisibilityArray == NULL) {
        return 0;
    }
    for (int i = 2; i < n; ++i) {
        if (!divisibilityArray[i]) {
            printf("%d\n", i);
        }
    }
    free(divisibilityArray);
}
