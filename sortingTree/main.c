#include <stdio.h>
#include "sorting.h"
#include "tree.h"

int main(void) {
    bool errorCode = false;
    Value array[] = {"123", "234", "567","91" ,"12"};
    int arraySize = 5;
    Node * root = buildTree(array, arraySize, &errorCode);
    int external = 0;
    treeSort(root, array, &external, &errorCode);
    int a = 0;
}
