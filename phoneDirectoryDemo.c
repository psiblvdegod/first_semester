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
    char * newName = malloc(sizeof(char) * 50);
    char * newNumber = malloc(sizeof(char) * 30);
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
        //if (feof(file)) break;
    }
}

void printAllContacts(Contact * contacts[], int amountOfContacts) {
    printf("Your %d contacts:\n", amountOfContacts);
    for (int i = 0; i < amountOfContacts; ++i) {
        printf("%s %s\n", contacts[i]->name, contacts[i]->number);
    }
}

Contact * searchByNumber(Contact * contacts[], int amountOfContacts) {
    char * key = malloc(sizeof(char) * 30) ;
    scanf("%s", key);
    for (int i = 0; i < amountOfContacts; ++i) {
        if (!strcmp(contacts[i]->number, key)) {
            return contacts[i];
        }
    }
    return NULL;
}

Contact * searchByName(Contact * contacts[], int amountOfContacts) {
    char * key = malloc(sizeof(char) * 30) ;
    scanf("%s", key);
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

void actions(Contact * contacts, int * amountOfContacts, Contact ** mainPointer, int userAnswer) {
    if((!(*amountOfContacts)) && (2 <= userAnswer) && (userAnswer <= 5)) {
        printf("The function is not available because contacts list is empty.\n");
        return;
    }
    switch (userAnswer) {
        case 0:
        printf("end.\n");
        break;
        case 1:
        printf("Enter name and phone number.\nDo not separate name and surname with a space.\n");
        newContact(contacts, amountOfContacts, mainPointer);
        printf("Contact added.\n");
        break;
        case 2:
        printAllContacts(contacts, *amountOfContacts);
        break;
        case 3:
        printf("Enter name you want to find:\n");
        Contact * resultSearchName = searchByName(contacts, *amountOfContacts);
        if (resultSearchName == NULL) {
            printf("Number does not exist.\n");
        }
        else {
            printf("%s %s\n", resultSearchName->name, resultSearchName->number);
        }
        break;
        case 4:
        printf("Enter number you want to find:\n");
        Contact * resultSearchNumber = searchByNumber(contacts, *amountOfContacts);
        if (resultSearchNumber == NULL) {
            printf("Number does not exist.\n");
        }
        else {
            printf("%s %s\n", resultSearchNumber->name, resultSearchNumber->number);
        }
        break;
        case 5:
        saveContacts(contacts, *amountOfContacts);
        break;
        default:
        printf("Invalid value.\n");
        break;
    }
}

int main(void) {
    FILE * file = fopen("text.txt", "r");
    Contact * contacts[100];
    int amountOfContacts = 0;
    Contact * mainPointer = NULL;
    readContactsFromFile(contacts, &amountOfContacts, &mainPointer, file);
    int userAnswer = -1;
    const char * message = "0 exit\n1 add contact\n2 print contacts\n3 search by name\n4 search by number\n5 save contacts\n";
    printf("%s", message);
    while (userAnswer) {
        scanf("%d", &userAnswer);
        actions(contacts, &amountOfContacts, &mainPointer, userAnswer);
        printf("%s", message);
    }
    fclose(file);
}
