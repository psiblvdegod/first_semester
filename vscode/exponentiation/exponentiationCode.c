#include <setjmp.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

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
                                                    
                                                      int main(void) {
                                                          printf("Linear time exponentiation\n");
                                                              for (int i = -5; i < 11; ++i) {
                                                                    printf("%lf\n", power(2, i));
                                                                        }
                                                                            printf("\nLog time exponentiation\n");
                                                                                for (int k = -5; k < 11; ++k) {
                                                                                      printf("%lf\n", ultraPower(2, k));
                                                                                          }
                                                                                            }
                                                                                            