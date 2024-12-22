#include "phoneDirectory.h"
#include "queryProcessing.h"
#include "tests.h"

int main(void) {
    int errorCode = 0;
    phoneDirectoryTest(&errorCode);
    if (reportError(errorCode)) {
        return errorCode;
    }
    const char *filePath = "../text.txt";
    Directory directory = createDirectory(100, &errorCode);
    if (reportError(errorCode)) {
        return errorCode;
    }
    fillDirectoryFromFile(directory, filePath, &errorCode);
    if (reportError(errorCode)) {
        return errorCode;
    }
    while (queryProcessing(directory, filePath, &errorCode)) {
        errorCode = 0;
    }
    return errorCode;
}
