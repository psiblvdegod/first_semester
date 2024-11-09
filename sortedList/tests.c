#include "tests.h"

bool listTests() {
    bool errorCode = false;
    List * list = createList(&errorCode);
    Position position = getGuardian(list, &errorCode);
    if (list == NULL) {
        return false;
    }
    addElement(list, position, 10, &errorCode);
    addElement(list, getNext(position, &errorCode), 20, &errorCode);
    Value test1 = getValue(getPrevious(list, getLast(list, &errorCode), &errorCode), &errorCode);
    bool test2 = listSize(list) == 3;
    Position pos1 = getNext(getGuardian(list, &errorCode), &errorCode);
    deleteElement(list, pos1, &errorCode);
    return test1 == 10 && test2  && !errorCode;
}
