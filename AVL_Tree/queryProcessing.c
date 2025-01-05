#include "queryProcessing.h"
#include "typeDefinitions.h"
#include "errorCode.h"
#include <stdio.h>

void processQuery(Dictionary *dictionary, int userQuery, int *errorCode) {
    if (dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (userQuery == '0') {
        return;
    }
    else if (userQuery == '1') {
        char value[VALUE_MAX_SIZE] = {'0'};
        char key [KEY_MAX_SIZE] = {'0'};
        printf("Enter value and key.\n");
        if (scanf("%s%s", value, key) != 2) {
            printf("Invalid value.\n");
            return;
        }
        while (getchar() != '\n');
        addToDictionary(dictionary, value, key, errorCode);
    }
    else if (userQuery == '2' || userQuery == '3') {
        char key [KEY_MAX_SIZE] = {'0'};
        printf("Enter key.\n");
        if (scanf("%s", key) != 1) {
            printf("Invalid value.\n");
            return;
        }
        while (getchar() != '\n');
        Value result = searchInDictionary(dictionary, key, errorCode);
        if (*errorCode != NO_ERRORS) {
            return;
        }
        if (result == nullptr) {
            printf("No such element.\n");
        }
        else if (userQuery == '2') {
            printf("value: %s\n", result);
        }
        else {
            printf("There are value with such key in dictionary.\n");
        }
    }
    else if (userQuery == '4') {
        char key [KEY_MAX_SIZE] = {'0'};
        printf("Enter key.\n");
        if (scanf("%s", key) != 1) {
            printf("Invalid value.\n");
            return;
        }
        while (getchar() != '\n');
        deleteFromDictionary(dictionary, key, errorCode);
    }
    else {
        printf("Invalid value.\n");
    }
}