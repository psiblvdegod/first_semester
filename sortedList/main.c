#include "queryProcessing.h"
#include "errorCode.h"
#include "list.h"
#include "tests.h"

int main(void) {
    int errorCode = listTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    List *list = createList(&errorCode);
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    while (processQuery(list, &errorCode));

    deleteList(&list, &errorCode);
    return errorCode;
}