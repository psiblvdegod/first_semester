#include "theRevenant.h"
#include "list.h"

int positionOfTheRevenant (int mortality, int victimsAmount, bool * errorCode) {
    List * list = createList(&errorCode);
    if (list == NULL) {
        *errorCode = true;
        return -1;
    }
    Position mainPosition = NULL;
    for (int i = 1; i <= victimsAmount; ++i) {
        addElement(list, &mainPosition, i, errorCode);
    }
    Position currentPosition = getFirst(list, errorCode);
    for (int j = 1; listSize(list) > 1; ++j) {
        if (j == mortality) {
            deleteElement(list, &currentPosition, errorCode);
            j = 1;
        }
        currentPosition = getNext(currentPosition, errorCode);
    }
}