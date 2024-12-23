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
}