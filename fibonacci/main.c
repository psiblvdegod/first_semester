#include <stdio.h>
#include <stdbool.h>
#include <time.h>

int fibonacciIterative(int number) {
    int previousNumber = 0;
    int currentNumber = 1;
    for (;number > 1; --number) {
        int temp = previousNumber + currentNumber;
        previousNumber = currentNumber;
        currentNumber = temp;
    }
    return currentNumber;
}

int fibonacciRecursive(int currentNumber) {
    if (currentNumber == 0 || currentNumber == 1) {
        return currentNumber;
    }
    return fibonacciRecursive(currentNumber - 2) + fibonacciRecursive(currentNumber - 1);
}

bool test(){
    return fibonacciIterative(4) == 3 && fibonacciRecursive(4) == 3;
}

void recursiveTime() {
    for (int i = 1; i < 10; ++i) {
        clock_t startTime = clock();
        fibonacciRecursive(i * 5);
        const double duration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d: %lf\n", i * 5, duration);
    }
}

void iterativeTime() {
    for (int i = 1; i <= 10; ++i) {
        clock_t startTime = clock();
        fibonacciIterative(i * 1000);
        const double duration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d: %lf\n", i * 1000, duration);
    }
}

int main(void) {
    bool testStatus = test();
    if (!testStatus) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    printf("Fibonacci recursive method time\n");
    recursiveTime();
    printf("Fibonacci iterative method time\n");
    iterativeTime();
    printf("Recursive method gets very slow starting with ~45th element.\n");
}
