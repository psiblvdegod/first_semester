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
    addToList(list, "234", errorCode);
    addToList(list, "111", errorCode);
    addToList(list, "345", errorCode);
    addToList(list, "100", errorCode);
    deleteOddIndexes(list, errorCode);
    const char *expectedResult[] = {"123", "111", "100"};
    for (int i = 0; !isEmpty(list, errorCode); ++i) {
        if (strcmp(popFromList(list, errorCode), expectedResult[i]) != 0) {
            if (*errorCode == NO_ERRORS) {
                *errorCode = TESTS_FAILED_ERROR;
            }
        }
    }
    deleteList(&list, errorCode);
}