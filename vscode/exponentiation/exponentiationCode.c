#include <setjmp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

double power(int base, int exponent) {
    double result = 1.0;
        for (int i = 0; i < abs(exponent); ++ i) {
                result *= base;
                    }
                        if (exponent < 0) {
                                return 1.0 / ((double) result);
                                    }
                                        return result;
                                        }

                                        double ultraPower(int base, int exponent) {
                                            double result = 1.0;
                                                for (int i = 0; i < abs(exponent) / 2; ++i) {
                                                        result *= base;
                                                            }
                                                                result *= result;
                                                                    if (abs(exponent) % 2 == 1) {
                                                                            result *= base;
                                                                                }
                                                                                    if (exponent < 0) {
                                                                                            return 1.0 / result;
                                                                                                }
                                                                                                    return result;
                                                                                                    }

                                                                                                    bool test() {
                                                                                                        int array[] = {1, 2, 4, 8, 16};
                                                                                                            for (int k = 0; k < 5; ++k) {
                                                                                                                    if (power(2, k) != ultraPower(2, k ) || power(2, k) != array[k]) {
                                                                                                                              return false;
                                                                                                                                      }
                                                                                                                                          }
                                                                                                                                              return true;
                                                                                                                                              }

                                                                                                                                              int main(void) {
                                                                                                                                                  if (!test()) {
                                                                                                                                                          printf("Error. Test failed.\n");
                                                                                                                                                              }
                                                                                                                                                                  else {
                                                                                                                                                                          printf("Linear time exponentiation\n");
                                                                                                                                                                                  for (int i = -5; i < 11; ++i) {
                                                                                                                                                                                              printf("%lf\n", power(2, i));
                                                                                                                                                                                                      }
                                                                                                                                                                                                              printf("\nLog time exponentiation\n");
                                                                                                                                                                                                                      for (int k = -5; k < 11; ++k) {
                                                                                                                                                                                                                                  printf("%lf\n", ultraPower(2, k));
                                                                                                                                                                                                                                          }
                                                                                                                                                                                                                                              }
                                                                                                                                                                                                                                              }