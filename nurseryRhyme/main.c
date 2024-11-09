#include "list.h"
#include "tests.h"
#include <stdio.h>
#include "theRevenant.h"

int main(void) {
    printf("%d ", listTests());
    bool errorCode = false;
    int n = 0, m = 0;
    printf("Enter n, m\n");
    int inputValidation = scanf("%d%d", &n, &m);
    if (inputValidation != 2) {
        printf("Invalid value.\n");
        return -1;
    }

    int result = getPositionOfTheRevenant(m, n, &errorCode);
    printf("You will survive if pick %d number.\n", result);
}