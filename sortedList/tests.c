#include "tests.h"
#include "list.h"

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR (-1)
#define NO_ERRORS 0

void listTests(int *errorCode) {
    List list = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    const bool test1 = insertInList(list, "123", errorCode);
    const bool test2 = searchInList(list, "123", errorCode);
    const bool test3 = deleteFromList(list, "123", errorCode);
    const bool test4 = !searchInList(list, "123", errorCode);
    const bool test5 = !deleteFromList(list, "123", errorCode);
    deleteList(&list, errorCode);
    const bool test = test1 && test2 && test3 && test4 && test5;
    if (*errorCode == NO_ERRORS && !test) {
        *errorCode = TESTS_FAILED_ERROR;
    }
}
