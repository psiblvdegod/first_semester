#include "queryProcessing.h"
#include "errorCode.h"
#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

int main(void) {
    test();
    Node *root = NULL;
    int errorCode = NO_ERRORS;
    char userQuery = 1;
    while (userQuery) {
        printf("0 - exit // 1 - insert // 2 - search // 3 - check // 4 - dispose\n");
        scanf("%c", &userQuery);
        queryProcessing(&root, userQuery, &errorCode);
    }
}