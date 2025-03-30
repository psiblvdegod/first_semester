#include "test.h"
#include "list.h"
#include <string.h>

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR (-1)
#define NO_ERRORS 0

void listTests(int *errorCode) {
    List *list = createList(errorCode);
    if (*errorCode) {
        return;
    }
    addToList(list, "123", errorCode);
    addToList(list, "456", errorCode);
    const bool test1 = strcmp(popFromList(list, errorCode), "123") == 0;
    const bool test2 = strcmp(popFromList(list, errorCode), "456") == 0;
    const bool test = test1 && test2;
    if (*errorCode == NO_ERRORS && !test) {
        *errorCode = TESTS_FAILED_ERROR;
    }
    deleteList(&list, errorCode);
}

void copyListElements(int *errorCode) {
    List *list = createList(errorCode);
    if (*errorCode) {
        return;
    }
    addToList(list, "123", errorCode);
    addToList(list, "234", errorCode);
    addToList(list, "111", errorCode);
    addToList(list, "345", errorCode);
    addToList(list, "100", errorCode);
    copyListElementsByFirstSymbol(list, '1', errorCode);
    const char *expectedResult[] = {"123", "234", "111", "345", "100", "123", "111", "100"};
    for (int i = 0; !isEmpty(list, errorCode); ++i) {
        if (expectedResult[i] != popFromList(list, errorCode)) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
                deleteList(&list, errorCode);
                return;
            }
        }
    }
    deleteList(&list, errorCode);
}