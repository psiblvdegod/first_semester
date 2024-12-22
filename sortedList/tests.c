#include "tests.h"
#include "list.h"

void listTests(int *errorCode) {
    List list = createList(errorCode);
    if (*errorCode != 0) {
        return;
    }
    const bool test1 = insertInList(list, "123", errorCode);
    const bool test2 = searchInList(list, "123", errorCode);
    const bool test3 = deleteFromList(list, "123", errorCode);
    const bool test4 = !searchInList(list, "123", errorCode);
    const bool test5 = !deleteFromList(list, "123", errorCode);
    deleteList(&list, errorCode);
    const bool test = test1 && test2 && test3 && test4 && test5;
    if (*errorCode == 0 && !test) {
        *errorCode = -1;
    }
}
