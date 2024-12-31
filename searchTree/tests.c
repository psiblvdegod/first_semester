#include "tests.h"
#include "tree.h"
#include "errorCode.h"
#include <string.h>

int treeTests() {
    int errorCode = NO_ERRORS;
    Node *root = nullptr;
    root = insertInTree(root, "111", 1, &errorCode);
    root = insertInTree(root, "222", 2, &errorCode);
    root = insertInTree(root, "333", 3, &errorCode);
    root = insertInTree(root, "444", 4, &errorCode);
    if (errorCode != NO_ERRORS) {
        deleteTree(&root, &errorCode);
        return errorCode;
    }
    bool wasDeletionSuccessful = false;
    root = deleteFromTree(root, 1, &wasDeletionSuccessful, &errorCode);
    const bool test1 = strcmp(searchInTree(root, 3), "333") == 0;
    const bool test2 = searchInTree(root, 5) == NULL;
    deleteTree(&root, &errorCode);
    const bool test = test1 && test2 && wasDeletionSuccessful;
    if (errorCode == NO_ERRORS && !test) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}
