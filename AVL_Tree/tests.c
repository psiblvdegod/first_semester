#include "tests.h"
#include <string.h>

bool treeTests() {
    bool errorCode = false;
    Node * node1 = createNode("a", "1", &errorCode);
    Node * node2 = createNode("b", "2", &errorCode);
    Node * node3 = createNode("c", "3", &errorCode);
    Node * node4 = createNode("d", "4", &errorCode);
    Node * node5 = createNode("e", "5", &errorCode);
    Node * node6 = createNode("f", "6", &errorCode);
    Node * node0 = createNode("0", "0", &errorCode);
    Node * node7 = createNode("g", "7", &errorCode);
    Node * node8 = createNode("h", "8", &errorCode);
    Node * node9 = createNode("i", "9", &errorCode);
    Node * node10 = createNode("j", "A", &errorCode);

    Node * root = node8;
    root = insert(root, node9, &errorCode);
    errorCode = false;
    root = insert(root, node2, &errorCode);
    errorCode = false;
    root = insert(root, node1, &errorCode);
    errorCode = false;
    root = insert(root, node0, &errorCode);
    errorCode = false;
    root = insert(root, node4, &errorCode);
    errorCode = false;
    root = insert(root, node7, &errorCode);
    errorCode = false;
    root = insert(root, node10, &errorCode);
    errorCode = false;
    root = dispose(root, "8", &errorCode);
    errorCode = false;
    root = dispose(root, "2", &errorCode);
    errorCode = false;
    root = dispose(root, "4", &errorCode);
}