#include "functions.h"

void actions(Contact * contacts, int * amountOfContacts, Contact ** mainPointer, int userAnswer) {
    if((!(*amountOfContacts)) && (2 <= userAnswer) && (userAnswer <= 5)) {
        printf("The function is not available because contacts list is empty.\n");
        return;
    }
    switch (userAnswer) {
        case 0:
        printf("End.\n");
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
