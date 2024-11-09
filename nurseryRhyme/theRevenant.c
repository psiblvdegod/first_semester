#include "theRevenant.h"
#include "list.h"

int positionOfTheRevenant (int mortality, int victimsAmount, bool * errorCode) {
    List * list = createList(errorCode);
    if (list == NULL) {
        *errorCode = true;
        return -1;
    }
    Position creatingListPosition = NULL;
    for (int i = 1; i <= victimsAmount; ++i) {
        addElement(list, &creatingListPosition, i, errorCode);
    }
    creatingListPosition = NULL;
    Position currentPosition = getFirst(list, errorCode);
    for (int j = 1; listSize(list) > 1; ++j) {
        if (j == mortality) {
            Position temp = currentPosition;
            currentPosition = getNext(currentPosition, errorCode);
            deleteElement(list, &temp, errorCode);
            j = 0;
            continue;
        }
        currentPosition = getNext(currentPosition, errorCode);
    }
    return getValue(currentPosition, errorCode);
}