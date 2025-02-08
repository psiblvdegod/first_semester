#include "errorCode.h"
#include "tests.h"
#include "tree.h"
#include <string.h>

int treeTests() {
    int errorCode = NO_ERRORS;
    Node *root = nullptr;
    root = insertInTree(root, "222", 2, &errorCode);
    root = insertInTree(root, "111", 1, &errorCode);
    root = insertInTree(root, "444", 4, &errorCode);
    root = insertInTree(root, "333", 3, &errorCode);
    if (errorCode != NO_ERRORS) {
        deleteTree(&root, &errorCode);
        return errorCode;
    }
    const bool invariantTest1 = verifyBinarySearchTreeInvariant(root);
    bool wasDeletionSuccessful = false;
    root = deleteFromTree(root, 1, &wasDeletionSuccessful, &errorCode);
    const bool invariantTest2 = verifyBinarySearchTreeInvariant(root);
    const bool searchTest1 = strcmp(searchInTree(root, 3), "333") == 0;
    const bool searchTest2 = searchInTree(root, 5) == NULL;
    deleteTree(&root, &errorCode);
    const bool test = invariantTest1 && invariantTest2 && searchTest1 && searchTest2 && wasDeletionSuccessful;
    if (errorCode == NO_ERRORS && !test) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}
