#include "sorting.h"
#include <stdlib.h>

Node * buildTree(Value *array, const int arraySize, bool * errorCode) {
    Node * root = createNode(array[0], errorCode);
    for (int i = 1; i < arraySize; ++i) {
        Node * newNode = createNode(array[i], errorCode);
        root = insert(root, newNode, errorCode);
    }
    return root;
}

void symmetricalTraversal(Node * node, Value * array, int * external, bool * errorCode) {
    if (node == NULL) {
        return;
    }
    symmetricalTraversal(getChild(node, left), array, external, errorCode);
    array[*external] = getValue(node);
    ++(*external);
    symmetricalTraversal(getChild(node, right), array, external, errorCode);
}

void treeSort(Value *array, const int arraySize, bool * errorCode) {
    Node * root = buildTree(array, arraySize, errorCode);
    int externalVariableForTraversal = 0;
    symmetricalTraversal(root, array, &externalVariableForTraversal, errorCode);
}