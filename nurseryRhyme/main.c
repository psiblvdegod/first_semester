#include "list.h"
#include "tests.h"
#include "theRevenant.h"
#include <stdio.h>

int main(void) {
    if (!listTests() || !theRevenantTest()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    bool errorCode = false;
    int n = 0, m = 0;
    printf("Enter n, m\n");
    int inputValidation = scanf("%d%d", &n, &m);
    if (inputValidation != 2 || n < 1 || m < 1) {
        printf("Invalid value.\n");
        return -1;
    }
    int result = getPositionOfTheRevenant(m, n, &errorCode);
    if (errorCode) {
        printf("Error.\n");
        return -1;
    }
    printf("You will survive if pick %d number.\n", result);
}
