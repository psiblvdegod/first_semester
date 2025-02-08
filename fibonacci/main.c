#include "fibonacci.h"
#include <stdio.h>
#include <stdbool.h>
#include <time.h>

void printIterativeTime() {
    for (int i = 1; i <= 10; ++i) {
        const clock_t startTime = clock();
        calculateFibonacciIterative(i * 1000);
        const double duration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d: %lf\n", i * 1000, duration);
    }
}

void printRecursiveTime() {
    for (int i = 1; i < 10; ++i) {
        const clock_t startTime = clock();
        calculateFibonacciRecursive(i * 5);
        const double duration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d: %lf\n", i * 5, duration);
    }
}

bool test(){
    const bool test1 = calculateFibonacciIterative(4) == 3;
    const bool test2 = calculateFibonacciRecursive(4) == 3;
    return test1 && test2;
}

int main(void) {
    if (!test()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    printf("Fibonacci iterative method time\n");
    printIterativeTime();
    printf("Fibonacci recursive method time\n");
    printRecursiveTime();
    printf("Recursive method gets very slow starting with ~45th element.\n");
}
