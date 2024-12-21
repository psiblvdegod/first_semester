#include "queryProcessing.h"
#include <stdio.h>
#include <stdlib.h>

bool errorMessage(const int errorCode) {
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
    return true;
}

bool queryProcessing(Directory directory, const char *filePath, int *errorCode) {
    char userQuery = '0';
    printf("0 - save // 1 - add // 2 - print all // 3 - search by name // 4 - search by number\n");
    const int inputValidation = scanf("%c", &userQuery);
    while (getchar() != '\n');
    if (inputValidation != 1) {
        *errorCode = 9;
        return errorMessage(*errorCode);
    }
    if (userQuery == '1') {
        printf("Enter name and phone number.\nDo not separate name and surname with a space.\n");
        char *newName = calloc(50, sizeof(char));
        char *newNumber = calloc(30, sizeof(char));
        if (newName == NULL || newNumber == NULL) {
            *errorCode = 44;
            return errorMessage(*errorCode);
        }
        const int inputValidation = scanf("%s %s", newName, newNumber);
        while (getchar() != '\n');
        if (inputValidation != 2) {
            *errorCode = 9;
            free(newName);
            free(newNumber);
            return errorMessage(*errorCode);
        }
        addContact(directory, newName, newNumber, errorCode);
        if (*errorCode == 0) {
            printf("Contact added.\n");
        }
    }
    else if (userQuery == '2') {
        printAllContacts(directory);
    }
    else if (userQuery == '3') {
        printf("Enter name you want to find:\n");
        char name[50] = {0};
        const int inputValidation = scanf("%s", name);
        while (getchar() != '\n');
        if (inputValidation != 1) {
            *errorCode = 9;
            return errorMessage(*errorCode);
        }
        const char *number = searchByName(directory, name, errorCode);
        if (*errorCode == 0) {
            if (number == NULL) {
                printf("No such contact.\n");
            }
            else {
                printf("%s - %s\n", name, number);
            }
        }
    }
    else if (userQuery == '4') {
        printf("Enter number you want to find:\n");
        char number[30] = {0};
        const int inputValidation = scanf("%s", number);
        while (getchar() != '\n');
        if (inputValidation != 1) {
            *errorCode = 9;
            return true;
        }
        const char *name = searchByNumber(directory, number, errorCode);
        if (*errorCode == 0) {
            if (name == NULL) {
                printf("No such contact.\n");
            }
            else {
                printf("%s - %s\n", name, number);
            }
        }
    }
    else if (userQuery == '5') {
        saveContactsToFile(directory, filePath, errorCode);
    }
    else {
        *errorCode = 9;
    }
    return errorMessage(*errorCode);
}