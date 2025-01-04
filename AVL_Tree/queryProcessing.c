#include "queryProcessing.h"
#include "errorCode.h"
#include <stdlib.h>
#include <stdio.h>

void queryProcessing(Node **root, const char userQuery, int *errorCode) {
    if (userQuery == '1') {
        printf("Enter value and key.\n");
        char value[50] = {'0'};
        char key[50] = {'0'};
        scanf("%s%s", value, key);
        bool isHeightChanged = false;
        *root = insert(*root, createNode(value, key, errorCode), &isHeightChanged);
    }
    else if (userQuery == '2' || userQuery == '3') {
        printf("Enter key.\n");
        char key[50] = {'0'};
        scanf("%s", key);
        const char *result = search(*root, key);
        if (result == NULL) {
            printf("No such key.\n");
        }
        else if (userQuery == '2') {
            printf("Value: %s\n", result);
        }
        else {
            printf("+\n");
        }
    }
    else if (userQuery == '4') {
        printf("Enter key.\n");
        char key[50] = {'0'};
        scanf("%s", key);
        bool isHeightChanged = false;
        *root = dispose(*root, key, &isHeightChanged);
    }
    else if (userQuery != '0') {
        printf("Invalid value.\n");
    }
}

