#include "phoneDirectory.h"
#include "tests.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void queryProcessing(Directory directory, const char userQuery, bool * errorCode) {
    if (userQuery == '1') {
        printf("Enter name and phone number.\nDo not separate name and surname with a space.\n");
        char *newName = calloc(50, sizeof(char));
        char *newNumber = calloc(30, sizeof(char));
        if (newName == NULL || newNumber == NULL) {
            printf("Memory allocation error.\n");
            return;
        }
        const int inputValidation = scanf("%s %s", newName, newNumber);
        while (getchar() != '\n');
        if (inputValidation != 2) {
            printf("Invalid value.\n");
            return;
        }
        addContact(directory, newName, newNumber, errorCode);
        if (*errorCode) {
            printf("Contact adding error.\n");
        }
        printf("Contact added.\n");
    }
    else if (userQuery == '2') {
        printAllContacts(directory);
    }
    else if (userQuery == '3') {
        printf("Enter name you want to find:\n");
        char name[50] = {0};
        const int inputValidation = scanf("%s", name);
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            return;
        }
        searchByName(directory, name);
    }
    else if (userQuery == '4') {
        printf("Enter number you want to find:\n");
        char number[30] = {0};
        const int inputValidation = scanf("%s", number);
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            return;
        }
        searchByNumber(directory, number);
    }
    if (*errorCode) {
        printf("Something went wrong.\n");
        *errorCode = false;
    }
}

int main(void) {
    if (!phoneDirectoryTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    bool errorCode = false;
    const char * filePath = "../text.txt";
    FILE * file = fopen(filePath, "r");
    if (file == NULL) {
        printf("File opening error.\n");
        return -1;
    }
    Directory directory = createDirectory(100, &errorCode);
    fillDirectoryFromFile(directory, file, &errorCode);
    if (errorCode) {
        printf("Directory creating error.\n");
        return -1;
    }
    char userQuery = -1;
    while (userQuery) {
        printf("0 exit // 1 add contact // 2 print contacts\n3 search by name // 4 search by number // 5 save contacts\n");
        scanf("%c", &userQuery);
        while (getchar() != '\n');
        if (userQuery < '0' || userQuery > '5') {
            printf("Invalid value.\n");
            continue;
        }
        queryProcessing(directory, userQuery, &errorCode);
        if (userQuery == '5') {
            saveContactsToFile(directory, filePath, &errorCode);
            printf("%s.\n", errorCode ? "File saving error" : "Contacts saved");
        }
    }
    fclose(file);
}
