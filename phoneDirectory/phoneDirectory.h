#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Contact {
    char * name;
    char * number;
    struct Contact * previous;
} Contact;

Contact * addContact(Contact * contacts[], int * amountOfContacts, char * addName, char * addNumber);

Contact * newContact(Contact * contacts[], int * amountOfContacts);

Contact * readContactsFromFile(Contact * contacts[], int * amountOfContacts,, FILE * file);

void printAllContacts(Contact * contacts[], int amountOfContacts);

Contact * searchByNumber(Contact * contacts[], int amountOfContacts, char * key);

Contact * searchByName(Contact * contacts[], int amountOfContacts, char * key);

void saveContacts(Contact * contacts[], int amountOfContacts);