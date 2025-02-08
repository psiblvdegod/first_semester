#include "errorCode.h"
#include "tests.h"
#include "list.h"

int listTests() {
    int errorCode = NO_ERRORS;
    List *list = createList(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    const bool test1 = insertInList(list, "123", &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    const bool test2 = searchInList(list, "123", &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    const bool test3 = deleteFromList(list, "123", &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    const bool test4 = !searchInList(list, "123", &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    const bool test5 = !deleteFromList(list, "123", &errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    deleteList(&list, &errorCode);
    const bool test = test1 && test2 && test3 && test4 && test5;
    if (errorCode == NO_ERRORS && !test) {
        errorCode = TESTS_FAILED_ERROR;
    }
    return errorCode;
}
