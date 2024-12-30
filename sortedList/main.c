#include "list.h"
#include "tests.h"
#include "queryProcessing.h"


int main(void) {
    int errorCode = 0;
    listTests(&errorCode);
    if (errorCode != 0) {
        return errorCode;
    }
    List *list = createList(&errorCode);
    if (errorCode != 0) {
        return errorCode;
    }
    while(queryProcessing(list, &errorCode));

    deleteList(&list, &errorCode);
    return errorCode;
}