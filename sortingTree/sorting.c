#include "sorting.h"

//buildsTree with array's values
Node * buildTree(Value *array, const int arraySize, bool * errorCode) {
    Node * root = createNode(array[0], errorCode);
    for (int i = 1; i < arraySize; ++i) {
        Node * newNode = createNode(array[i], errorCode);
        root = insert(root, newNode);
    }
    return root;
}
//the main part of treeSort() function
//requires integer external variable = 0
void symmetricalTraversal(Node * node, Value * array, int * externalVariable, bool * errorCode) {
    if (node == NULL) {
        return;
    }
    symmetricalTraversal(getChild(node, left), array, externalVariable, errorCode);
    array[*externalVariable] = getValue(node);
    ++(*externalVariable);
    symmetricalTraversal(getChild(node, right), array, externalVariable, errorCode);
}

void treeSort(Value *array, const int arraySize, bool * errorCode) {
    Node * root = buildTree(array, arraySize, errorCode);
    int externalVariable = 0;
    symmetricalTraversal(root, array, &externalVariable, errorCode);
}