#include "queryProcessing.h"
#include "dictionary.h"
#include "errorCode.h"
#include "tests.h"
#include <stdio.h>

int main(void) {
    int errorCode = treeTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    Dictionary *dictionary = createDictionary(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    int userQuery = 1;
    while (userQuery != '0') {
        printf("0 - exit // 1 - insert // 2 - search // 3 - check // 4 - delete\n");
        userQuery = getchar();
        while (getchar() != '\n');
        processQuery(dictionary, userQuery, &errorCode);
        while (getchar() != '\n');
        if (errorCode != NO_ERRORS) {
            break;
        }
    }
    deleteDictionary(&dictionary, &errorCode);
    return errorCode;
}