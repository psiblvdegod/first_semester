#include "phoneDirectory.h"
#include "tests.h"

void queryProcessing(Directory directory, const int userQuery, bool * errorCode) {
    if (!(*errorCode)) {
        printf("Something went wrong.\n");
        return;
    }
    if (userQuery == 1) {
        printf("Enter name and phone number.\nDo not separate name and surname with a space.\n");
        const char *newName = calloc(50, sizeof(char));
        const char *newNumber = calloc(30, sizeof(char));
        if (newName == NULL || newNumber == NULL) {
            printf("Memory allocation error.\n");
            return;
        }
        addContact(directory, newName, newNumber);
        printf("Contact added.\n");
    }
    else if (userQuery == 2) {
        printAllContacts(directory);
    }
    else if (userQuery == 3) {
        printf("Enter name you want to find:\n");
        char name[50] = {0};
        const int inputValidation = scanf("%s", name);
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            return;
        }
        searchByName(directory, name);
    }
    else if (userQuery == 4) {
        printf("Enter number you want to find:\n");
        char number[30] = {0};
        const int inputValidation = scanf("%s", number);
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            return;
        }
        searchByNumber(directory, number);
    }
    else if (userQuery == 5) {
        printAllContacts(directory);
    }
}

int main(void) {
    if (!phoneDirectoryTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    bool errorCode = false;
    FILE * file = fopen("/Users/psiblvdegod/Desktop/homework/phoneDirectory/text.txt", "r");
    if (file == NULL) {
        printf("File opening error.\n");
        return -1;
    }
    Directory directory = createDirectory(100, &errorCode);
    fillDirectoryFromFile(directory, file, &errorCode);
    printf("0 exit // 1 add contact // 2 print contacts\n3 search by name // 4 search by number // 5 save contacts\n");
    int userQuery = -1;
    while (userQuery) {
        const int inputValidation = scanf("%d", &userQuery);
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            continue;
        }
        while (getchar() != '\n');
        queryProcessing(directory, userQuery, &errorCode);
    }
    fclose(file);
}
