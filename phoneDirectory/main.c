#include "phoneDirectory.h"

void actions(Contact * contacts, int * amountOfContacts, Contact ** mainPointer, int userAnswer, int * errorCode ) {
    if (!(*errorCode)) {
        printf("Somehing went wrong.\n");
        return;
    }
    switch (userAnswer) {
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
        char keyName[50] = {0};
        scanf("%s", keyName);
        Contact * resultSearchName = searchByName(contacts, *amountOfContacts, keyName);
        if (resultSearchName == NULL) {
            printf("Contact does not exist.\n");
        }
        else {
            printf("Name: %s\nNumber: %s\n", resultSearchName->name, resultSearchName->number);
        }
        break;
        case 4:
        printf("Enter number you want to find:\n");
        char keyNumber[30] = {0};
        scanf("%s", keyNumber);
        Contact * resultSearchNumber = searchByNumber(contacts, *amountOfContacts, keyNumber);
        if (resultSearchNumber == NULL) {
            printf("Contact does not exist.\n");
        }
        else {
            printf("Name: %s\nNumber: %s\n", resultSearchNumber->name, resultSearchNumber->number);
        }
        break;
        case 5:
        saveContacts(contacts, *amountOfContacts);
        break;
    }
}

bool test() {
    FILE * file = fopen("test.txt", "r+");
    Contact * contacts[5];
    int amountOfContacts = 0;
    Contact * testPointer = NULL;
    readContactsFromFile(contacts, &amountOfContacts, &testPointer, file);
    const bool testRead = (amountOfContacts == 1) && (!strcmp(contacts[0]->name, "test")) && (!strcmp(contacts[0]->number, "1"));
    addContact(contacts, &amountOfContacts, &testPointer, "test", "2");
    const bool testAdd = !strcmp(contacts[1]->name, "test") && !strcmp(contacts[1]->number, "2");
    Contact * search1 = searchByName(contacts, amountOfContacts, "test");
    Contact * search2 = searchByNumber(contacts, amountOfContacts, "2");
    const bool testSearch = (search1 == contacts[0]) && (search2 == contacts[1]);
    return testRead && testAdd && testSearch;
    
}

int main(void) {
    if (!test()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    FILE * file = fopen("text.txt", "r");
    Contact * contacts[100];
    int amountOfContacts = 0;
    Contact * mainPointer = NULL;
    readContactsFromFile(contacts, &amountOfContacts, &mainPointer, file);
    printf("0 exit\n1 add contact\n2 print contacts\n3 search by name\n4 search by number\n5 save contacts\n");
    int userAnswer = -1;
    while (userAnswer) {
        int errorCode = scanf("%d", &userAnswer);
        while (getchar() != '\n');
        actions(contacts, &amountOfContacts, &mainPointer, userAnswer, &errorCode);
    }
    fclose(file);
}
