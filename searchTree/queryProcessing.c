#include "queryProcessing.h"
#include "dictionary.h"
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
    const int key = (int)strtol(buffer, nullptr, 10);
    if (errno != 0) {
        *errorCode = QUERY_READING_ERROR;
        errno = 0;
        return -1;
    }
    return key;
}

void processQuery(Dictionary *dictionary, const int userQuery, int *errorCode) {
    if (userQuery == 1) {
        printf("Enter value and key.\n");
        char value[WORD_MAX_SIZE] = {'0'};
        if (scanf("%s", value) != 1) {
            printf("Invalid value.\n");
            return;
        }
        const int key = scanNumber(errorCode);
        if (*errorCode != NO_ERRORS) {
            if (*errorCode == QUERY_READING_ERROR) {
                *errorCode = NO_ERRORS;
                printf("Invalid value.\n");
            }
            return;
        }
        const bool wasAddingSuccessful = addToDictionary(dictionary, value, key, errorCode);
        printf("Element was%s added.\n", wasAddingSuccessful ? "" : " not");
    }
    else if (userQuery == 2 || userQuery == 3) {
        printf("Enter key.\n");
        const int key = scanNumber(errorCode);
        if (*errorCode != NO_ERRORS) {
            if (*errorCode == QUERY_READING_ERROR) {
                *errorCode = NO_ERRORS;
                printf("Invalid value.\n");
            }
            return;
        }
        const char *value = searchInDictionary(dictionary, key, errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
        if (value == NULL) {
            printf("No such key.\n");
        }
        else if (userQuery == 2) {
            printf("value: %s\n", value);
        }
        else {
            printf("There are value with such key in the list.\n");
        }
    }
    else if (userQuery == 4) {
        printf("Enter key.\n");
        const int key = scanNumber(errorCode);
        if (*errorCode != NO_ERRORS) {
            if (*errorCode == QUERY_READING_ERROR) {
                *errorCode = NO_ERRORS;
                printf("Invalid value.\n");
            }
            return;
        }
        const bool wasDeletionSuccessful = deleteFromDictionary(dictionary, key, errorCode);
        printf("Element was%s deleted.\n", wasDeletionSuccessful ? "" : " not");
    }
    else if (userQuery != 0) {
        printf("Invalid value.\n");
    }
}


