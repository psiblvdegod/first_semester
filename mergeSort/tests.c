#include "tests.h"
#include <stdio.h>

bool mergeTest() {

}

bool mergeSortTest() {
    bool errorCode = false;
    Node node = NULL;
    node = addElement(node, (Contact) {"qwe", "222"}, &errorCode);
    node = addElement(node, (Contact) {"asd", "111"}, &errorCode);
    node = addElement(node, (Contact) {"zxc", "333"}, &errorCode);
    node = mergeSort(node, &errorCode);
    bool test1 = !strcmp(getValue(node, &errorCode).value, "111");
    bool test2 = !strcmp(getValue(getNext(node, &errorCode), &errorCode).value, "222");
    bool test3 = !strcmp(getValue(getNext(getNext(node, &errorCode), &errorCode), &errorCode).value, "333");
    return test1 && test2 && test3 && !errorCode;
}