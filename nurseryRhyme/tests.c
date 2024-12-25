#include "tests.h"
#include "errorCode.h"
#include <stdlib.h>

void listTests(int *errorCode) {
    List *list = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addToList(list, 1, errorCode);
    addToList(list, 2, errorCode);
    addToList(list, 3, errorCode);
    addToList(list, 4, errorCode);
    addToList(list, 5, errorCode);
    addToList(list, 6, errorCode);
    addToList(list, 7, errorCode);
    addToList(list, 8, errorCode);
    addToList(list, 9, errorCode);

    int a = 0;
}


/*
bool theRevenantTest() {
    int errorCode = 0;
    const int test1 = getPositionOfTheRevenant(2, 10, &errorCode);
    const int test2 = getPositionOfTheRevenant(7, 7, &errorCode) ;
    const int test3 = getPositionOfTheRevenant(7, 11, &errorCode) ;
    const bool test = test1 && test2 && test3;
    if (errorCode == 0 && !test) {
        return -1;
    }
    return errorCode;
}
*/