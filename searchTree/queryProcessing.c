#include "queryProcessing.h"
#include "dictionary.h"
#include "errorCode.h"
#include <stdio.h>

void processQuery(Dictionary *dictionary, const int userQuery, int *errorCode) {
    if (userQuery == '1') {
        printf("Enter value and key.\n");
        char value[WORD_MAX_SIZE] = {'0'};
        if (scanf("%s", value) != 1) {
            printf("Invalid value.\n");
            return;
        }
        int key = -1;
        if (scanf("%d", &key) != 1) {
            printf("Invalid value.\n");
            return;
        }
        bool wasAddingSuccessful = addToDictionary(dictionary, value, key, errorCode);
        printf("Element was%s added.\n", wasAddingSuccessful ? "" : " not");
    }
    else if (userQuery == '2' || userQuery == '3') {
        printf("Enter key.\n");
        int key = 0;
        if (scanf("%d", &key) != 1) {
            printf("Invalid value.\n");
            return;
        }
        const char *value = searchInDictionary(dictionary, key, errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
        if (value == nullptr) {
            printf("No such key.\n");
        }
        else if (userQuery == '2') {
            printf("value: %s\n", value);
        }
        else {
            printf("There are value with such key in the list.\n");
        }
    }
    else if (userQuery == '4') {
        printf("Enter key.\n");
        int key = 0;
        scanf("%d", &key);
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
    else if (userQuery != '0') {
        printf("Invalid value.\n");
    }
}