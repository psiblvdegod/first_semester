#include "queryProcessing.h"
#include <stdio.h>
#include <stdlib.h>

bool reportError(const int errorCode) {
    if (errorCode == 0) {
        return false;
    }
    else if (errorCode == 100) {
        printf("Directory is overflowed.\n");
        return false;
    }
    else if (errorCode == 9) {
        printf("Invalid value.\n");
        return false;
    }

    else if (errorCode == 1) {
        printf("Incorrect arguments passed to function.\n");
    }
    else if (errorCode == 44) {
        printf("Memory allocation error.\n");
    }
    else if (errorCode == 15) {
        printf("File opening error.\n");
    }
    else if (errorCode == 139) {
        printf("Dereference NULL pointer.\n");
    }
    return true;
}

bool queryProcessing(Directory directory, const char *filePath, int *errorCode) {
    char userQuery = '0';
    printf("0 - quit // 1 - add // 2 - print all // 3 - search by name // 4 - search by number // 5 - save\n");
    int inputValidation = scanf("%c", &userQuery);
    while (getchar() != '\n');
    if (inputValidation != 1) {
        *errorCode = 9;
        return !reportError(*errorCode);
    }
    switch (userQuery) {
        case '0':
            break;
        case '1':
            printf("Enter name and phone number.\nDo not separate name and surname with a space.\n");
            char *newName = calloc(50, sizeof(char));
            char *newNumber = calloc(30, sizeof(char));
            if (newName == NULL || newNumber == NULL) {
                *errorCode = 44;
                break;
            }
            inputValidation = scanf("%s %s", newName, newNumber);
            while (getchar() != '\n');
            if (inputValidation != 2) {
                *errorCode = 9;
                free(newName);
                free(newNumber);
                break;
            }
            addContact(directory, newName, newNumber, errorCode);
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
                *errorCode = 9;
                break;
            }
            const char *foundNumber = searchByName(directory, name, errorCode);
            if (*errorCode != 0) {
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
                *errorCode = 9;
                break;
            }
            const char *foundName = searchByNumber(directory, number, errorCode);
            if (*errorCode != 0) {
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
            *errorCode = 9;
            break;
    }
    return !reportError(*errorCode) && userQuery != '0';
}