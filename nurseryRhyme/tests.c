#include "tests.h"
#include "errorCode.h"

void listTests(int *errorCode) {
    List *list = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addToList(list, 1, errorCode);
    addToList(list, 2, errorCode);
    addToList(list, 3, errorCode);
    addToList(list, 4, errorCode);
    Node *head = getHead(list, errorCode);
    deleteNext(head, errorCode);
    head = getNext(head, errorCode);
    head = getNext(head, errorCode);
    deleteNext(head, errorCode);
    head = getNext(head, errorCode);
    deleteNext(head, errorCode);
    const bool test = getValue(head, errorCode) == 3;
    if (*errorCode == NO_ERRORS && !test) {
        *errorCode = TESTS_FAILED_ERROR;
    }
}

void survivorTest(int *errorCode) {
    const int test1 = findSafePlace(2, 10, errorCode);
    const int test2 = findSafePlace(7, 7, errorCode) ;
    const int test3 = findSafePlace(7, 11, errorCode) ;
    const bool test = test1 && test2 && test3;
    if (*errorCode != NO_ERRORS && !test) {
        *errorCode = TESTS_FAILED_ERROR;
    }
}