#include "theRevenant.h"
#include "list.h"
#include "errorCode.h"

/*
int getPositionOfTheRevenant(const int mortality, const int numberOfVictims, int *errorCode) {
    List list = NULL;
    add(&list, 0, errorCode);
    List node = list;
    for (int i = 0; i < numberOfVictims; ++i) {
        add(&node, i, errorCode);
    }
    if (*errorCode != NO_ERRORS) {
        return -1;
    }
    for (int i = 0, k = 0; k < numberOfVictims - 1; ++i) {
        if (i == mortality) {
            delete(&list, errorCode);
            ++k;
            i = 0;
        }
    }
    return getValue(list, errorCode);
}
 */