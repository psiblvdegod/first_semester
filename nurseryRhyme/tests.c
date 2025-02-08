#include "tests.h"
#include "errorCode.h"

void listTests(int *errorCode) {
    List *list = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    addToList(list, 1, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    addToList(list, 2, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    addToList(list, 3, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    addToList(list, 4, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    Node *head = getHead(list, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    deleteNext(list, head, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    head = getNext(head, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    head = getNext(head, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    deleteNext(list, head, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    head = getNext(head, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    deleteNext(list, head, errorCode);
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    const bool test = getValue(head, errorCode) == 3;
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return;
    }
    deleteList(&list, errorCode);
    if (*errorCode == NO_ERRORS && !test) {
        *errorCode = TESTS_FAILED_ERROR;
    }
}

void safePlaceTest(int *errorCode) {
    const bool test1 = findSafePlace(2, 10, errorCode) == 5;
    if (*errorCode != NO_ERRORS) {
        return;
    }
    const bool test2 = findSafePlace(7, 7, errorCode) == 5;
    if (*errorCode != NO_ERRORS) {
        return;
    }
    const bool test3 = findSafePlace(7, 11, errorCode) == 5;
    const bool test = test1 && test2 && test3;
    if (*errorCode != NO_ERRORS && !test) {
        *errorCode = TESTS_FAILED_ERROR;
    }
}