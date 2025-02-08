#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "phoneDirectory.h"
#include "errorCode.h"

typedef struct Contact {
    const char *name;
    const char *number;
} Contact;

typedef struct Contacts {
    Contact **contacts;
    int size;
    int amountOfContacts;
} Contacts;

Directory createDirectory(const int size, int *errorCode) {
    if (size < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    Directory directory = calloc(1, sizeof(Contacts));
    Contact **contacts = calloc(size, sizeof(Contact*));
    if (directory == NULL || contacts == NULL) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
        free(directory);
        free(contacts);
        return NULL;
    }
    for (int i = 0; i < size; ++i) {
        contacts[i] = calloc(1, sizeof(Contact));
        if (contacts[i] == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            for (int k = i; k >= 0; --k) {
                free(contacts[k]);
            }
            return NULL;
        }
    }
    directory->contacts = contacts;
    directory->size = size;
    return directory;
}

void addContact(Directory directory, const char *newName, const char *newNumber, int *errorCode) {
    if (directory == NULL || directory->contacts == NULL || newName == NULL || newNumber == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (directory->amountOfContacts == directory->size) {
        *errorCode = DIRECTORY_IS_OVERFLOWED;
        return;
    }
    directory->contacts[directory->amountOfContacts]->name = newName;
    directory->contacts[directory->amountOfContacts]->number = newNumber;
    ++directory->amountOfContacts;
}

void fillDirectoryFromFile(Directory directory, const char *filePath, int *errorCode) {
    if (directory == NULL || filePath == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return;
    }
    while (true) {
        if (directory->amountOfContacts == directory->size) {
            *errorCode = DIRECTORY_IS_OVERFLOWED;
            break;
        }
        char *newName = calloc(50, sizeof(char));
        char *newNumber = calloc(30, sizeof(char));
        if (newName == NULL || newNumber == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            free(newName);
            free(newNumber);
            break;
        }
        if (fscanf(file, "%s%s", newName, newNumber) != 2) {
            break;
        }
        addContact(directory, newName, newNumber, errorCode);
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    fclose(file);
}

void printAllContacts(Directory directory, int *errorCode) {
    if (directory == NULL || directory->contacts == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (directory->amountOfContacts == 0) {
        printf("Directory is empty.\n");
        return;
    }
    printf("Your contacts:\n");
    for (int i = 0; i < directory->amountOfContacts; ++i){
        Contact *currentContact = directory->contacts[i];
        if (currentContact == NULL) {
            *errorCode = DEREFERENCE_NULL_POINTER;
            return;
        }
        printf("%s - %s\n", currentContact->name, currentContact->number);
    }
}

const char *searchByName(Directory directory, const char *key, int *errorCode) {
    if (directory == NULL || directory->contacts == NULL || key == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    for (int i = 0; i < directory->amountOfContacts; ++i){
        Contact *currentContact = directory->contacts[i];
        if (currentContact == NULL || currentContact->name == NULL) {
            *errorCode = DIRECTORY_IS_OVERFLOWED;
            return NULL;
        }
        if (strcmp(currentContact->name, key) == 0) {
            return currentContact->number;
        }
    }
    return NULL;
}

const char *searchByNumber(Directory directory, const char *key, int *errorCode) {
    if (directory == NULL || directory->contacts == NULL ||key == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return NULL;
    }
    for (int i = 0; i < directory->amountOfContacts; ++i){
        Contact *currentContact = directory->contacts[i];
        if (currentContact == NULL || currentContact->number == NULL) {
            *errorCode = DEREFERENCE_NULL_POINTER;
            return NULL;
        }
        if (strcmp(currentContact->number, key) == 0) {
            return currentContact->name;
        }
    }
    return NULL;
}

void saveContactsToFile(Directory directory, const char *filePath, int *errorCode) {
    if (filePath == NULL || directory == NULL || directory->contacts == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return;
    }
    for (int i = 0; i < directory->amountOfContacts; ++i) {
        Contact *currentContact = directory->contacts[i];
        if (currentContact == NULL) {
            *errorCode = DEREFERENCE_NULL_POINTER;
            fclose(file);
            return;
        }
        fprintf(file, "%s %s\n", currentContact->name, currentContact->number);
    }
    fclose(file);
}

void deleteDirectory(Directory *directory, int *errorCode) {
    if (directory == NULL || *directory == NULL || (*directory)->contacts == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    Contact *currentContact = (*directory)->contacts[0];
    for (int i = 1; currentContact != NULL; ++i) {
        Contact *temp = currentContact;
        currentContact = (*directory)->contacts[i];
        free(temp);
    }
    free(*directory);
    *directory = NULL;
}