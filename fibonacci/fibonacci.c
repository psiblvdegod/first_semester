#include "fibonacci.h"

int calculateFibonacciIterative(const int number) {
    int previousNumber = 0;
    int currentNumber = 1;
    for (int i = 1; i < number; ++i) {
        int temp = previousNumber + currentNumber;
        previousNumber = currentNumber;
        currentNumber = temp;
    }
    return currentNumber;
}

int calculateFibonacciRecursive(const int number) {
    if (number == 0 || number == 1) {
        return number;
    }
    return calculateFibonacciRecursive(number - 2) + calculateFibonacciRecursive(number - 1);
}
