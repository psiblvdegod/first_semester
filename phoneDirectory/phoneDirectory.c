#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "phoneDirectory.h"

typedef struct Contact {
    const char * name;
    const char * number;
} Contact;

typedef struct Contacts {
    Contact ** contacts;
    int amountOfContacts;
} Contacts;

Directory createDirectory(const int size, bool * errorCode) {
    Directory directory = calloc(1, sizeof(Contacts));
    Contact ** contacts = calloc(size, sizeof(Contact));
    if (directory == NULL || contacts == NULL || size < 1) {
        *errorCode = true;
        return NULL;
    }
    directory->contacts = contacts;
    return directory;
}

void addContact(Directory directory, const char * newName, const char * newNumber, bool * errorCode) {
    Contact * newContact = calloc(1, sizeof(Contact));
    if (directory == NULL || newContact == NULL) {
        *errorCode = true;
        return;
    }
    newContact->name = newName;
    newContact->number = newNumber;
    directory->contacts[directory->amountOfContacts] = newContact;
    ++directory->amountOfContacts;
}

void fillDirectoryFromFile(Directory directory, FILE * file, bool * errorCode) {
    while (true) {
        char * newName = calloc(50, sizeof(char));
        char * newNumber = calloc(30, sizeof(char));
        if (newName == NULL || newNumber == NULL) {
            *errorCode = true;
            return;
        }
        if (fscanf(file, "%s%s", newName, newNumber) != 2) {
            return;
        }
        addContact(directory, newName, newNumber, errorCode);
    }
}

void printAllContacts(Directory directory) {
    printf("Your contacts:\n");
    for (int i = 0; i < directory->amountOfContacts; ++i){
        Contact * currentContact = directory->contacts[i];
        printf("%s - %s\n", currentContact->name, currentContact->number);
    }
}

void searchByName(Directory directory, const char * key) {
    for (int i = 0; i < directory->amountOfContacts; ++i){
        Contact * currentContact = directory->contacts[i];
        if (strcmp(currentContact->name, key) == 0) {
            printf("%s - %s\n", currentContact->name, currentContact->number);
            return;
        }
    }
    printf("There is no such contact.\n");
}

void searchByNumber(Directory directory, const char * key) {
    for (int i = 0; i < directory->amountOfContacts; ++i){
        Contact * currentContact = directory->contacts[i];
        if (strcmp(currentContact->number, key) == 0) {
            printf("%s - %s\n", currentContact->name, currentContact->number);
            return;
        }
    }
    printf("There is no such contact.\n");
}

void saveContactsToFile(Directory directory, const char * filePath, bool * errorCode) {
    if (filePath == NULL) {
        *errorCode = true;
        return;
    }
    FILE * file = fopen(filePath, "w");
    if (file == NULL) {
        *errorCode = true;
        return;
    }
    for (int i = 0; i < directory->amountOfContacts; ++i) {
        Contact * currentContact = directory->contacts[i];
        fprintf(file, "%s %s\n", currentContact->name, currentContact->number);
    }
    fclose(file);
}
