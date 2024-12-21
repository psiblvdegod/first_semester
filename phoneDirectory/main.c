#include "phoneDirectory.h"
#include "tests.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool errorMessage(int *errorCode) {
    if (*errorCode == 0) {
        return false;
    }
    else if (*errorCode == 100) {
        printf("Directory is overflowed.\n");
        *errorCode = 0;
        return false;
    }
    else if (*errorCode == 9) {
        printf("Invalid value.\n");
        *errorCode = 0;
        return false;
    }

    else if (*errorCode == 1) {
        printf("Incorrect arguments passed to function.\n");
    }
    else if (*errorCode == 44) {
        printf("Memory allocation error.\n");
    }
    else if (*errorCode == 15) {
        printf("File opening error.\n");
    }
    return true;
}

void queryProcessing(Directory directory, const char *filePath, int *errorCode) {
    int userQuery = 0;
    printf("0 - save // 1 - add // 2 - print all // 3 - search by name // 4 - search by number\n");
    const int inputValidation = scanf("%d", &userQuery);
    while (getchar() != '\n');
    if (inputValidation != 1) {
        *errorCode = 9;
        return;
    }
    if (userQuery == 1) {
        printf("Enter name and phone number.\nDo not separate name and surname with a space.\n");
        char *newName = calloc(50, sizeof(char));
        char *newNumber = calloc(30, sizeof(char));
        if (newName == NULL || newNumber == NULL) {
            *errorCode = 44;
            return;
        }
        const int inputValidation = scanf("%s %s", newName, newNumber);
        while (getchar() != '\n');
        if (inputValidation != 2) {
            *errorCode = 9;
            free(newName);
            free(newNumber);
            return;
        }
        addContact(directory, newName, newNumber, errorCode);
        if (*errorCode == 0) {
            printf("Contact added.\n");
        }
    }
    else if (userQuery == 2) {
        printAllContacts(directory);
    }
    else if (userQuery == 3) {
        printf("Enter name you want to find:\n");
        char name[50] = {0};
        const int inputValidation = scanf("%s", name);
        while (getchar() != '\n');
        if (inputValidation != 1) {
            *errorCode = 9;
            return;
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
    else if (userQuery == 4) {
        printf("Enter number you want to find:\n");
        char number[30] = {0};
        const int inputValidation = scanf("%s", number);
        while (getchar() != '\n');
        if (inputValidation != 1) {
            *errorCode = 9;
            return;
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
    else if (userQuery == 0) {
        saveContactsToFile(directory, filePath, errorCode);
    }
}

int main(void) {
    if (!phoneDirectoryTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    int errorCode = 0;
    const char * filePath = "../text.txt";

    Directory directory = createDirectory(100, &errorCode);
    if (errorMessage(&errorCode)) {
        return errorCode;
    }
    fillDirectoryFromFile(directory, filePath, &errorCode);
    if (errorMessage(&errorCode)) {
        return errorCode;
    }
    while (!errorMessage(&errorCode)) {
        queryProcessing(directory, filePath, &errorCode);
    }
    return errorCode;
}
