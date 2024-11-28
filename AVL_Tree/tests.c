#include "tests.h"
#include <string.h>

bool treeTests() {
    bool errorCode = false;
    Node *node1 = createNode("a", "1", &errorCode);
    Node *node2 = createNode("b", "2", &errorCode);
    Node *node3 = createNode("c", "3", &errorCode);
    Node *node4 = createNode("d", "4", &errorCode);
    Node *root = node1;
    root = insert(root, node2, &errorCode);
    errorCode = false;
    root = insert(root, node3, &errorCode);
    errorCode = false;
    root = insert(root, node4, &errorCode);
    errorCode = false;
    root = dispose(root, "3", &errorCode);
    errorCode = false;
    Value value1 = findValueByKey(root, "1");
    Value value3 = findValueByKey(root, "3");
    return !errorCode && !strcmp(value1, "a") && value3 == NULL;
}