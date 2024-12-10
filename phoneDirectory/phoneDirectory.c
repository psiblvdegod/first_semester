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
    Directory directory = calloc(size, sizeof(Contact));
    if (directory == NULL) {
        *errorCode = true;
    }
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

void addCustomContact(Directory directory, bool * errorCode) {
    char * newName = calloc(50, sizeof(char));
    char * newNumber = calloc(30, sizeof(char));
    if (newName == NULL || newNumber == NULL) {
        *errorCode = true;
        return;
    }
    scanf("%s%s", newName, newNumber);
    createContact(directory, newName, newNumber);
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

Contact * searchByNumber(Contact * contacts[], int amountOfContacts, char * key) {
    for (int i = 0; i < amountOfContacts; ++i) {
        if (!strcmp(contacts[i]->number, key)) {
            return contacts[i];
        }
    }
    return NULL;
}

Contact * searchByName(Contact * contacts[], int amountOfContacts, char * key) {
    for (int i = 0; i < amountOfContacts; ++i) {
        if (!strcmp(contacts[i]->name, key)) {
            return contacts[i];
        }
    }
    return NULL;
}

void saveContacts(Contact * contacts[], int amountOfContacts) {
    FILE * file = fopen("text.txt", "w");
    for (int i = 0; i < amountOfContacts; ++i) {
        fprintf(file, "%s %s", contacts[i]->name, contacts[i]->number);
        if (i + 1 < amountOfContacts) {
            fprintf(file, "\n");
        }
    }
    printf("Contacts saved.\n");
    fclose(file);
}
