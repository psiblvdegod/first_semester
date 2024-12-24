#include "queryProcessing.h"
#include "errorCode.h"
#include <stdio.h>
#include <stdlib.h>

bool queryProcessing(Directory directory, const char *filePath, int *errorCode) {
    char userQuery = '0';
    printf("0 - quit // 1 - add // 2 - print all // 3 - search by name // 4 - search by number // 5 - save\n");
    int inputValidation = scanf("%c", &userQuery);
    while (getchar() != '\n');
    if (inputValidation != 1) {
        printf("Invalid value.\n");
        return true;
    }
    switch (userQuery) {
        case '0':
            break;
        case '1':
            printf("Enter name and phone number.\nDo not separate name and surname with a space.\n");
            char *newName = calloc(50, sizeof(char));
            char *newNumber = calloc(30, sizeof(char));
            if (newName == NULL || newNumber == NULL) {
                *errorCode = MEMORY_ALLOCATION_ERROR;
                return false;
            }
            inputValidation = scanf("%s %s", newName, newNumber);
            while (getchar() != '\n');
            if (inputValidation != 2) {
                printf("Invalid value.\n");
                free(newName);
                free(newNumber);
                break;
            }
            addContact(directory, newName, newNumber, errorCode);
            if (*errorCode) {
                free(newName);
                free(newNumber);
                if (*errorCode == DIRECTORY_IS_OVERFLOWED) {
                    printf("Directory is overflowed.\n");
                    *errorCode = NO_ERRORS;
                }
            }
            break;
        case '2':
            printAllContacts(directory, errorCode);
            break;
        case '3':
            printf("Enter name you want to find:\n");
            char name[50] = {0};
            inputValidation = scanf("%s", name);
            while (getchar() != '\n');
            if (inputValidation != 1) {
                printf("Invalid value.\n");
                break;
            }
            const char *foundNumber = searchByName(directory, name, errorCode);
            if (*errorCode != NO_ERRORS) {
                break;
            }
            if (foundNumber == NULL) {
                printf("No such contact.\n");
            }
            else {
                printf("%s - %s\n", name, foundNumber);
            }
            break;
        case '4':
            printf("Enter number you want to find:\n");
            char number[50] = {0};
            inputValidation = scanf("%s", number);
            while (getchar() != '\n');
            if (inputValidation != 1) {
                printf("Invalid value.\n");
                break;
            }
            const char *foundName = searchByNumber(directory, number, errorCode);
            if (*errorCode != NO_ERRORS) {
                break;
            }
            if (foundName == NULL) {
                printf("No such contact.\n");
            }
            else {
                printf("%s - %s\n", foundName, number);
            }
            break;
        case '5':
            saveContactsToFile(directory, filePath, errorCode);
            break;
        default:
            printf("Invalid value.\n");
            break;
    }
    return *errorCode == NO_ERRORS && userQuery != '0';
}