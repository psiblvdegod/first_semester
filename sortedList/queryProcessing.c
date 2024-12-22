#include "queryProcessing.h"
#include <stdio.h>
#include <stdlib.h>

bool queryProcessing(List list, int *errorCode) {
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
            Value newValue = calloc(50, sizeof(char));
            if (newValue == NULL) {
                *errorCode = 44;
                free(newValue);
                return false;
            }
            printf("Enter value you want to add. No more 50 symbols\n");
            inputValidation = scanf("%s", newValue);
            while(getchar() != '\n');
            if (inputValidation != 1) {
                printf("Invalid value.\n");
                free(newValue);
                break;
            }
            const bool wasAdded = insertElement(list, newValue, errorCode);
            if (*errorCode) {
                free(newValue);
            }
            printf("Element was%sadded.\n", wasAdded ? " " : " not ");
            break;
        }
        case '2': {
            Value deletingValue = calloc(50, sizeof(char));
            if (deletingValue == NULL) {
                *errorCode = 44;
                free(deletingValue);
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
            const bool wasDeleted = deleteElement(list, deletingValue, errorCode);
            printf("Element was%sdeleted.\n", wasDeleted ? " " : " not ");
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
    return *errorCode == 0 && userQuery != '0';
}