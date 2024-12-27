#include "queryProcessing.h"
#include "errorCode.h"
#include "tree.h"
#include "tests.h"
#include <stdio.h>

int main(void) {
    int errorCode = NO_ERRORS;
    treeTests(&errorCode);
    Node *root = NULL;
    int userQuery = -1;
    while (userQuery) {
        printf("0 - exit // 1 - insert // 2 - search // 3 - check // 4 - dispose\n");
        userQuery = scanNumber(&errorCode);
        queryProcessing(&root, userQuery, &errorCode);
        if (errorCode != NO_ERRORS) {
            if (errorCode == QUERY_READING_ERROR) {
                printf("Invalid value.\n");
                errorCode = NO_ERRORS;
            }
            else {
                break;
            }
        }
    }
    deleteTree(&root, &errorCode);
    return errorCode;
}