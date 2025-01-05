#include "queryProcessing.h"
#include "dictionary.h"
#include "errorCode.h"
#include "tests.h"
#include <stdio.h>

int main(void) {
    int errorCode = stackTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = AVLTreeTest();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = dictionaryTest();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = invariantTest("../test.txt");;
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    Dictionary *dictionary = createDictionary(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    int userQuery = '_';
    while (userQuery != '0') {
        printf("0 - quit // 1 - add // 2 - search // 3 - check // 4 - delete\n");
        userQuery = getchar();
        while (getchar() != '\n');
        processQuery(dictionary, userQuery, &errorCode);
        if (errorCode != NO_ERRORS) {
            break;
        }
    }
    deleteDictionary(&dictionary, &errorCode);
    return errorCode;
}