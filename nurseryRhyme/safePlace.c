#include "safePlace.h"
#include "errorCode.h"
#include "list.h"

int findSafePlace(const int mortality, const int numberOfVictims, int *errorCode) {
    if (mortality < 1 || numberOfVictims < 1) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return -1;
    }
    List *list = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return -1;
    }
    for (int i = 0; i < numberOfVictims; ++i) {
        addToList(list, i, errorCode);
        if (*errorCode != NO_ERRORS) {
            deleteList(&list, errorCode);
            return -1;
        }
    }
    Node *node = getHead(list, errorCode);
    for (int i = 0, k = 0; i < numberOfVictims - 1; ++k) {
        if (k == mortality - 1) {
            deleteNext(list, node, errorCode);
            ++i;
            k = 0;
        }
        node = getNext(node, errorCode);
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    Value result = getValue(node, errorCode);
    deleteList(&list, errorCode);
    return result;
}