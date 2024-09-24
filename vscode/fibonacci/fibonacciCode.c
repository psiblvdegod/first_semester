#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

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

                                      int main(void) {
                                          bool testStatus = test();
                                              if (!testStatus) {
                                                    printf("Error. Tests failed.\n");
                                                        }
                                                            else {
                                                                    printf("Enter sequence length:\n");
                                                                            int input;
                                                                                    scanf("%d", &input);
                                                                                            printf("Fibonacci Iterative Method:\n");
                                                                                                    int *result = fibonacciIterative(input);
                                                                                                            for (int i = 0; i < input; ++i) {
                                                                                                                        printf("%d\n", *(result + i));
                                                                                                                                }
                                                                                                                                        printf("\n\nFibonacci Recursive Method\n");
                                                                                                                                                int product;
                                                                                                                                                        for (int i = 0; i < input; ++i) {
                                                                                                                                                                    product = fibonacciRecursive(i);
                                                                                                                                                                                printf("%d\n", product);
                                                                                                                                                                                    }
                                                                                                                                                                                      }
                                                                                                                                                                                      }