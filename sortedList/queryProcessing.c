#include "queryProcessing.h"
#include "errorCode.h"
#include <stdio.h>
#include <stdlib.h>

bool queryProcessing(List *list, int *errorCode) {
    if (errorCode == NULL) {
        return false;
    }
    printf("0 - quit // 1 - add // 2 - delete // 3 - print all\n");
    char userQuery;
    int inputValidation = scanf("%c", &userQuery);
    while(getchar() != '\n');
    if (inputValidation != 1) {
        printf("Invalid value.\n");
        return true;
    }
    switch (userQuery) {
        case '0':
            break;
        case '1': {
            char newValue[50] = { '0' };
            printf("Enter value you want to add. No more 50 symbols\n");
            inputValidation = scanf("%s", newValue);
            while(getchar() != '\n');
            if (inputValidation != 1) {
                printf("Invalid value.\n");
                break;
            }
            const bool wasInsertSuccessful = insertInList(list, newValue, errorCode);
            printf("Element was%s added.\n", wasInsertSuccessful ? "" : " not");
            break;
        }
        case '2': {
            Value deletingValue = calloc(50, sizeof(char));
            if (deletingValue == NULL) {
                *errorCode = MEMORY_ALLOCATION_ERROR;
                return false;
            }
            printf("Enter value you want to delete. No more 50 symbols\n");
            inputValidation = scanf("%s", deletingValue);
            while(getchar() != '\n');
            if (inputValidation != 1) {
                printf("Invalid value.\n");
                free(deletingValue);
                break;
            }
            const bool wasDeletionSuccessful = deleteFromList(list, deletingValue, errorCode);
            printf("Element was%s deleted.\n", wasDeletionSuccessful ? "" : " not");
            free(deletingValue);
            break;
        }
        case '3': {
            printList(list, errorCode);
            break;
        }
        default:
            printf("Invalid value.\n");
    }
    if (*errorCode != NO_ERRORS) {
        printf("Something went wrong.\n");
        return false;
    }
    return userQuery != '0';
}