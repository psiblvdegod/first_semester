#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
    char * name;
    char * number;
    struct Contact * previous;
} Contact;

Contact * addContact(Contact * contacts, int * amountOfContacts, char * newName, char * newNumber, bool * errorCode) {
    Contact * newContact = calloc(1, sizeof(Contact));
    if (newContact == NULL) {
        errorCode = true;
        return NULL;
    }
    newContact->name = newName;
    newContact->number = newNumber;
    newContact->previous = contacts;
    ++(*amountOfContacts);
    return newContact;
}

void newContact(Contact * contacts, const int * amountOfContacts) {
    char * newName = calloc(50, sizeof(char));
    char * newNumber = calloc(30, sizeof(char));
    scanf("%s%s", newName, newNumber);
    addContact(contacts, amountOfContacts, mainPointer, newName, newNumber);
}

void readContactsFromFile(Contact ** contacts, int * amountOfContacts, Contact ** mainPointer, FILE * file) {
    while (true) {
        char * readName = calloc(50, sizeof(char));
        char * readNumber = calloc(30, sizeof(char));
        if (fscanf(file, "%s%s", readName, readNumber) != 2) {
            break;
        }
        *contacts =  addContact(contacts, amountOfContacts, mainPointer, readName, readNumber);
    }
}

void printAllContacts(Contact * contacts, int amountOfContacts) {
    printf("Your %d contacts:\n", amountOfContacts);
    while (contacts != NULL) {
        printf("%s - %s\n", contacts->number, contacts->number);
        contacts = contacts->previous;
    }
}

Contact * searchByNumber(Contact * contacts, char * key) {
    while (contacts != NULL) {
        if (!strcmp(contacts->number, key)) {
            return contacts;
        }
        contacts = contacts->previous;
    }
    return NULL;
}

Contact * searchByName(Contact * contacts, char * key) {
    while (contacts != NULL) {
        if (!strcmp(contacts->name, key)) {
            return contacts;
        }
        contacts = contacts->previous;
    }
    return NULL;
}

void saveContacts(Contact * contacts) {
    FILE * file = fopen("text.txt", "w");
    if (file == NULL) {
        *errorCode = true;
        return;
    }
    while(contacts != NULL) {
        fprintf(file, "%s %s\n", contacts->name, contacts->number);
        contacts = contacts->previous;
    }
    printf("Contacts saved.\n");
    fclose(file);
}