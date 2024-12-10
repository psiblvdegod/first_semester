#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Contacts * Directory;

Directory createDirectory(int size, bool * errorCode);

void addContact(Directory directory, const char * newName, const char * newNumber);

void fillDirectoryFromFile(Directory directory, FILE * file, bool * errorCode);

void printAllContacts(Directory directory);

void searchByName(Directory directory, const char * key);

void searchByNumber(Directory directory, const char * key);

void saveContacts(Directory directory);