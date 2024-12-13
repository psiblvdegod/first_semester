#include "tests.h"
#include "phoneDirectory.h"

bool phoneDirectoryTest() {
    bool errorCode = false;
    Directory directory = createDirectory(10, &errorCode);
    addContact(directory, "1st", "2nd", &errorCode);
    addContact(directory, "3rd", "4th", &errorCode);
    addContact(directory, "5th", "6th", &errorCode);
    return !errorCode;
}