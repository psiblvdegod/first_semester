#include <stdio.h>
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
    if (directory == NULL || contacts == NULL) {
        *errorCode = true;
        return NULL;
    }
    directory->contacts = contacts;
    return directory;
}

void addContact(Directory directory, const char * newName, const char * newNumber) {
    Contact * newContact = calloc(1, sizeof(Contact));
    if (newContact == NULL) {
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
        if (fscanf(file, "%s%s", newName, newNumber) != 2) {
            break;
        }
        addContact(directory, newName, newNumber);
    }
}

void printAllContacts(Directory directory) {
    printf("Your contacts:\n");
    Contact * currentContact = directory->contacts[0];
    for (int i = 1; i < directory->amountOfContacts; ++i){
        printf("%s - %s\n", currentContact->name, currentContact->number);
        currentContact = directory->contacts[i];
    }
}

void searchByName(Directory directory, const char * key) {
    Contact * currentContact = directory->contacts[0];
    for (int i = 1; i < directory->amountOfContacts; ++i){
        if (strcmp(currentContact->name, key) == 0) {
            printf("%s - %s\n", currentContact->name, currentContact->number);
            return;
        }
        currentContact = directory->contacts[i];
    }
    printf("There is no such contact.\n");
}

void searchByNumber(Directory directory, const char * key) {
    Contact * currentContact = directory->contacts[0];
    for (int i = 1; i < directory->amountOfContacts; ++i){
        if (strcmp(currentContact->number, key) == 0) {
            printf("%s - %s\n", currentContact->name, currentContact->number);
            return;
        }
        currentContact = directory->contacts[i];
    }
    printf("There is no such contact.\n");
}

void saveContacts(Directory directory) {
    FILE * file = fopen("text.txt", "w");
    Contact * currentContact = directory->contacts[0];
    for (int i = 1; i < directory->amountOfContacts; ++i) {
        fprintf(file, "%s %s\n", currentContact->name, currentContact->number);
    }
    fprintf(file, "\n");
    printf("Contacts saved.\n");
    fclose(file);
}
