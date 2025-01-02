#include "tree.h"
#include "parse.h"
#include "tests.h"
#include "errorCode.h"

int main(void) {
    int errorCode = stackTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    errorCode = treeTests();
    if (errorCode != NO_ERRORS) {
        return errorCode;
    }
    Node *root = buildTree("../text.txt", &errorCode);
    printTree(root, &errorCode);
    const int result = calculateTree(root, &errorCode);
    printf("\nresult: %d\n", result);
    return errorCode;
}