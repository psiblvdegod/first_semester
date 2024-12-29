#include "queryProcessing.h"
#include "errorCode.h"
#include <stdlib.h>
#include <stdio.h>

char *scanString(int *errorCode) {
    char *result = calloc(50, sizeof(char));
    if (result == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    if (scanf("%s", result) != 1) {
        *errorCode = QUERY_READING_ERROR;
        free(result);
    }
    while (getchar() != '\n');
    return result;
}

void queryProcessing(Node **root, const char userQuery, int *errorCode) {
    if (userQuery == '1') {
        printf("Enter value and key.\n");
        char *value = scanString(errorCode);
        char *key = scanString(errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
        bool isHeightChanged = false;
        *root = insert(*root, createNode(value, key, errorCode), &isHeightChanged);
        if (*errorCode != NO_ERRORS) {
            free(value);
            free(key);
        }
    }
    else if (userQuery == '2' || userQuery == '3') {
        printf("Enter key.\n");
        char *key = scanString(errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
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
        free(key);
    }
    else if (userQuery == '4') {
        printf("Enter key.\n");
        char *key = scanString(errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
        bool isHeightChanged = false;
        *root = dispose(*root, key, &isHeightChanged);
        free(key);
    }
    else if (userQuery != '0') {
        printf("Invalid value.\n");
    }
}

