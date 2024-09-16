#include <stdio.h>

int zeroCounterFunction(int inputArray[], int arrayLength) {
    int zeroCounter = 0;
    for (int i = 0; i < arrayLength; ++i) {
        if (inputArray[i] == 0) {
            zeroCounter += 1;
        }
    }
    return zeroCounter;
}

int main(void) {
    int array1[] = { 1, 0, 2, 0 ,3, 0, 4, 0, 5, 0, 6, 0, 7, 0, 8, 0 };
    int array1Length = sizeof(array1) / sizeof(int);
    int result = zeroCounterFunction(array1, array1Length);
    printf("%d\n", result);
}
