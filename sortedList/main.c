#include "list.h"
#include "tests.h"
#include "queryProcessing.h"

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR (-1)
#define NO_ERRORS 0

int main(void) {
    int errorCode = 0;
    listTests(&errorCode);
    if (errorCode != 0) {
        return errorCode;
    }
    List list = createList(&errorCode);
    if (errorCode != 0) {
        return errorCode;
    }
    while(queryProcessing(list, &errorCode));

    deleteList(&list, &errorCode);
    return errorCode;
}