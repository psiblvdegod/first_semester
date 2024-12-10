#include "tests.h"

bool phoneDirectoryTest() {
    bool errorCode = false;
    Directory directory = createDirectory(10, &errorCode);
    printf("phoneDirectoryTest()\n");
    addContact(directory, "first", "second", &errorCode);
    addContact(directory, "third", "fourth", &errorCode);
    printAllContacts(directory);
    addContact(directory, "ifYouSeeThis", "searchWorksProperly", &errorCode);
    searchByName(directory, "ifYouSeeThis");
    printf("test finished.\n\n");
    return !errorCode;
}