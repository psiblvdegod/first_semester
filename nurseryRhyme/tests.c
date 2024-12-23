#include "tests.h"

/*
bool listTests() {
    bool errorCode = false;
    List * list = createList(&errorCode);
    Position mainPointer = NULL;
    if (list == NULL) {
        return false;
    }
    addElement(list, &mainPointer, 10, &errorCode);
    addElement(list, &mainPointer, 20, &errorCode);
    Value test1 = getValue(getNext(getLast(list, &errorCode), &errorCode), &errorCode);
    Value test2 = getValue(getPrevious(list, getFirst(list, &errorCode), &errorCode), &errorCode);
    bool test3 = listSize(list) == 2;
    Position pos1 = getFirst(list, &errorCode);
    Position pos2 = getLast(list, &errorCode);
    deleteElement(list, pos2, &errorCode);
    deleteElement(list, pos1, &errorCode);
    deleteList(&list, &errorCode);
    return test1 == 10 && test2 == 20 && test3 && !errorCode;
}
*/
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
