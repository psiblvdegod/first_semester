#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Contacts * Directory;

Directory createDirectory(int size, bool * errorCode);
//adds new contact
void addContact(Directory directory, const char * newName, const char * newNumber, bool * errorCode);

void fillDirectoryFromFile(Directory directory, FILE * file, bool * errorCode);

void printAllContacts(Directory directory);

//prints contact or reports that it doesn't exist
void searchByName(Directory directory, const char * key);

//prints contact or reports that it doesn't exist
void searchByNumber(Directory directory, const char * key);

void saveContactsToFile(Directory directory, const char * filePath, bool * errorCode);