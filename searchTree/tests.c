#include "tests.h"
#include "tree.h"
#include <string.h>

void treeTests(int *errorCode) {
    Node *root = NULL;
    root = insert(root, "0", 0, errorCode);
    root = insert(root, "-10", -10, errorCode);
    root = insert(root, "10", 10, errorCode);
    root = insert(root, "20", 20, errorCode);
    root = insert(root, "15", 15, errorCode);
    int a = 0;
}
