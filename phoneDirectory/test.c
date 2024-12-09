#include "test.h"

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