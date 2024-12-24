#include "phoneDirectory.h"
#include "queryProcessing.h"
#include "tests.h"
#include "errorCode.h"

int main(void) {
    int errorCode = NO_ERRORS;
    phoneDirectoryTest(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    const char *filePath = "../text.txt";
    Directory directory = createDirectory(100, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    fillDirectoryFromFile(directory, filePath, &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    while (queryProcessing(directory, filePath, &errorCode));

    deleteDirectory(&directory, &errorCode);
    return errorCode;
}