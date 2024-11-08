#include "tests.h"

bool listTests() {
    bool errorCode = false;
    List * testList = createList(&errorCode);
    Position position = NULL;
    addElement(testList, &position, 1, &errorCode);
    addElement(testList, &position, 2, &errorCode);

    Position testGetFirst = getFirst(testList, &errorCode);
    Position testGetLast = getLast(testList, &errorCode);

    Value testGetNext = getValue(getNext(testGetFirst, &errorCode), &errorCode);
    Value testGetPrevious = getValue(getPrevious(testList, testGetLast, &errorCode), &errorCode);
    Position first = getFirst(testList, &errorCode);
    deleteElement(testList, &first, &errorCode);
    deleteList(&testList);
    return !errorCode && testGetNext == 2 && testGetPrevious == 1;
}