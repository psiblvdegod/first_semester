#include "phoneDirectory.h"
#include "queryProcessing.h"
#include "tests.h"

int main(void) {
    int errorCode = 0;
    phoneDirectoryTest(&errorCode);
    if (errorMessage(&errorCode)) {
        return errorCode;
    }
    const char *filePath = "../text.txt";
    Directory directory = createDirectory(100, &errorCode);
    if (errorMessage(&errorCode)) {
        return errorCode;
    }
    fillDirectoryFromFile(directory, filePath, &errorCode);
    if (errorMessage(&errorCode)) {
        return errorCode;
    }
    while (!errorMessage(&errorCode)) {
        queryProcessing(directory, filePath, &errorCode);
    }
    return errorCode;
}
