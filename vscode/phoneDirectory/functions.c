#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Contact {
    char * name;
    char * number;
    struct Contact * previous;
} Contact;

void addContact(Contact * contacts[], int * amountOfContacts, Contact ** mainPointer, char * addName, char * addNumber) {
    Contact * addPointer = malloc(sizeof(Contact));
    addPointer->name = addName;
    addPointer->number = addNumber;
    addPointer->previous = mainPointer;
    *mainPointer = addPointer;
    contacts[*amountOfContacts] = addPointer;
    ++(*amountOfContacts);
}

void newContact(Contact * contacts[], int * amountOfContacts, Contact ** mainPointer) {
    char * newName = calloc(50, sizeof(char));
    char * newNumber = calloc(30, sizeof(char));
    scanf("%s%s", newName, newNumber);
    addContact(contacts, amountOfContacts, mainPointer, newName, newNumber);
}

void readContactsFromFile(Contact * contacts[], int * amountOfContacts, Contact ** mainPointer, FILE * file) {
    while (1) {
        char * readName = calloc(50, sizeof(char));
        char * readNumber = calloc(30, sizeof(char));
        if (fscanf(file, "%s%s", readName, readNumber) != 2) {
            break;
        }
        addContact(contacts, amountOfContacts, mainPointer, readName, readNumber);
    }
}

void printAllContacts(Contact * contacts[], int amountOfContacts) {
    printf("Your %d contacts:\n", amountOfContacts);
    for (int i = 0; i < amountOfContacts; ++i) {
        printf("%s %s\n", contacts[i]->name, contacts[i]->number);
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
