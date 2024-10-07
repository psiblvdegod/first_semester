#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

int *fibonacciIterative(int sequenceLength) {
    int *sequence = malloc(sequenceLength);
    sequence[0] = 0;
    sequence[1] = 1;
    for (int i = 2; i < sequenceLength; ++i) {
        sequence[i] = sequence[i - 1] + sequence[i - 2];
    }
    free(sequence);
    return sequence;
}

int fibonacciRecursive(int currentNumber) {
    if (currentNumber == 0) {
        return 0;
    }
    if (currentNumber == 1) {
        return 1;
    }
    return fibonacciRecursive(currentNumber - 2) + fibonacciRecursive(currentNumber - 1);
}

bool test(){
    return fibonacciIterative(5)[4] == 3 && fibonacciRecursive(4) == 3;
}

void recursiveTime() {
    for (int i = 2; i < 10; ++i) {
        clock_t startTime = clock();
        double duration = 1;
        fibonacciRecursive(i * 5);
        duration = ((double) clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d: %lf\n", i * 5, duration);
    }
}

void iterativeTime() {
    for (int i = 1; i <= 10; ++i) {
        clock_t startTime = clock();
        double duration = 1;
        fibonacciIterative(i * 100);
        duration = ((double) clock() - startTime) / CLOCKS_PER_SEC;
        printf("%d: %lf\n", i * 100, duration);
    }
}

int main() {
    bool testStatus = test();
    if (!testStatus) {
        printf("Error. Tests failed.\n");
        return 0;
    }
    printf("Fibonacci recursive method time\n");
    recursiveTime();
    printf("Fibonacci iterative method time\n");
    iterativeTime();
    printf("Recursive method gets very slow starting with ~45th element.\n");
}
