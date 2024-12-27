#include "tests.h"
#include "tree.h"
#include "errorCode.h"
#include <string.h>

void treeTests(int *errorCode) {
    Node *root = NULL;
    root = insert(root, "0", 0, errorCode);
    root = insert(root, "-10", -10, errorCode);
    root = insert(root, "10", 10, errorCode);
    root = insert(root, "20", 20, errorCode);
    root = insert(root, "15", 15, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    root = dispose(root, 0, errorCode);
    root = dispose(root, -10, errorCode);
    root = dispose(root, 20, errorCode);
    root = dispose(root, -20, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    const bool searchTest1 = strcmp(search(root, 15), "15") == 0;
    const bool searchTest2 = search(root, -20) == NULL;
    const bool test = searchTest1 && searchTest2;
    deleteTree(&root, errorCode);
    if (*errorCode == NO_ERRORS && !test) {
        *errorCode = TESTS_FAILED_ERROR;
    }
}
