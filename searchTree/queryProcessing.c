#include "queryProcessing.h"
#include "errno.h"
#include "errorCode.h"
#include <stdlib.h>
#include <stdio.h>

int scanNumber(int *errorCode) {
    char buffer[16] = {'0'};
    if (scanf("%s", buffer) != 1) {
        *errorCode = QUERY_READING_ERROR;
        return -1;
    }
    const int key = (int)strtol(buffer, NULL, 10);
    if (errno != 0) {
        *errorCode = QUERY_READING_ERROR;
        errno = 0;
        return -1;
    }
    return key;
}

char *scanString(int *errorCode) {
    char *value = calloc(50, sizeof(char));
    if (value == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        return NULL;
    }
    if (scanf("%s", value) != 1) {
        *errorCode = QUERY_READING_ERROR;
        return NULL;
    }
    return value;
}

void queryProcessing(Node **root, const int userQuery, int *errorCode) {
    if (userQuery == 1) {
        printf("Enter value and key.\n");
        char *value = scanString(errorCode);
        const int key = scanNumber(errorCode);
        if (*errorCode != NO_ERRORS) {
            free(value);
            return;
        }
        *root = insert(*root, value, key, errorCode);
    }
    else if (userQuery == 2 || userQuery == 3) {
        printf("Enter key.\n");
        const int key = scanNumber(errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
        const char *value = search(*root, key);
        if (*errorCode != NO_ERRORS) {
            return;
        }
        if (value == NULL) {
            printf("No such key.\n");
        } else if (userQuery == 2) {
            printf("value: %s\n", value);
        } else {
            printf("There are value with such key in the list.\n");
        }
    }
    else if (userQuery == 4) {
        printf("Enter key.\n");
        const int key = scanNumber(errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
        *root = dispose(*root, key, errorCode);
    }
    else if (userQuery != 0) {
        *errorCode = QUERY_READING_ERROR;
    }
}


