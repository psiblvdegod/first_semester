#include "theRevenant.h"
#include "list.h"

int getPositionOfTheRevenant(const int mortality, const int numberOfVictims, int *errorCode) {
    Node *node = create(numberOfVictims, errorCode);
    if (*errorCode != 0) {
        return -1;
    }
    for (int i = 0, k = 0; k < numberOfVictims - 1; ++i) {
        if (i == mortality) {
            node = delete(node, errorCode);
            ++k;
            i = 0;
        }
        node = getNext(node, errorCode);
    }
    return getValue(node, errorCode);
}