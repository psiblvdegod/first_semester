#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h> 

typedef struct Contacts * Directory;

void addContact(Contact * contacts[], int * amountOfContacts, Contact ** mainPointer, char * addName, char * addNumber);
void newContact(Contact * contacts[], int * amountOfContacts, Contact ** mainPointer);
void readContactsFromFile(Contact * contacts[], int * amountOfContacts, Contact ** mainPointer, FILE * file);
void printAllContacts(Contact * contacts[], int amountOfContacts);
Contact * searchByNumber(Contact * contacts[], int amountOfContacts, char * key);
Contact * searchByName(Contact * contacts[], int amountOfContacts, char * key);
void saveContacts(Contact * contacts[], int amountOfContacts);
