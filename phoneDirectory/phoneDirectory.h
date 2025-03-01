#pragma once
#include <stdio.h>
#include <stdbool.h>

typedef struct Contacts *Directory;

// creates Directory with fixed size which stores contacts as "name - number".
Directory createDirectory(int size, int *errorCode);

// adds new contact to the directory.
void addContact(Directory directory, const char *newName, const char *newNumber, int *errorCode);

// adds contacts from file to directory.
// contact must be stored as "name number\n"
void fillDirectoryFromFile(Directory directory, const char *filePath, int *errorCode);

void printAllContacts(Directory directory, int *errorCode);

// prints contact or reports that it doesn't exist
const char *searchByName(Directory directory, const char *key, int *errorCode);

// prints contact or reports that it doesn't exist
const char *searchByNumber(Directory directory, const char *key, int *errorCode);

// opens file from filePath to write and saves contacts in directory to it.
void saveContactsToFile(Directory directory, const char *filePath, int *errorCode);

void deleteDirectory(Directory *directory, int *errorCode);