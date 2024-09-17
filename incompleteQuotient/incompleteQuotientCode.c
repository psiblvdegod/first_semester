#include <stdio.h>
#include <math.h>

int incompleteQuotient(int divisible, int divider) {
    if (divider == 0) {
        printf("Divider can not be zero.\n");
        return 0;
    }
    for (int quotient = -abs(divisible); quotient <= abs(divisible); ++quotient) {
        for (int remainder = 0; remainder < abs(divider); ++remainder) {
            if (divisible == (divider * quotient) + remainder) {
                return quotient;
            }
        }
    }
}

int main(void) {
    int inputDivisible = 1, inputDivider = 1;
    printf("Enter divisible and divider.\n");
    scanf("%d%d", &inputDivisible, &inputDivider);
    int result = incompleteQuotient(inputDivisible, inputDivider);
    printf("Incomplete quotient = %d.\n", result);
}
