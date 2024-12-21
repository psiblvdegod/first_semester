#include "tests.h"
#include "phoneDirectory.h"
#include <string.h>

bool phoneDirectoryTest() {
    int errorCode = 0;
    Directory directory = createDirectory(10, &errorCode);
    addContact(directory, "1st", "2nd", &errorCode);
    addContact(directory, "3rd", "4th", &errorCode);
    const bool test1 = strcmp(searchByName(directory, "1st", &errorCode), "2nd") == 0;
    const bool test2 = strcmp(searchByNumber(directory, "4th", &errorCode), "3rd") == 0;
    const bool test3 = searchByName(directory, "5th", &errorCode) == NULL;
    return test1 && test2 && test3 && !errorCode;
}