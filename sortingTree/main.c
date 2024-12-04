#include <stdio.h>
#include "sorting.h"
#include "tree.h"

int main(void) {
    bool errorCode = false;
    Value array[] = {"123", "234", "567","91" ,"12"};
    Node * root = buildTree(array, 5, &errorCode);
    printAllNodes(root, &errorCode);
    int a = 0;
}
