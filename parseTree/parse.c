#include "parse.h"
#include <stdlib.h>
#include <stdio.h>

Tree * buildTree(char * string, bool * errorCode) {
    Tree * tree = createTree(createNode(string[0], errorCode), errorCode);
    Stack * stack = createStack(errorCode);
    push(stack, getRoot(tree), errorCode);
    for (int i = 1; string[i] != '\0'; ++i) {
        Node * node = createNode(string[i], errorCode);
        Node * previousOperation = getHead(stack, errorCode);
        Node * leftChild = getChild(previousOperation, left, errorCode);
        Node * rightChild = getChild(previousOperation, right, errorCode);
        bool addChildFlag = false; // no elif xDD
        if (leftChild == NULL) {
            addChild(previousOperation, node, left, errorCode);
            addChildFlag = true;
        }
        if (rightChild == NULL && !addChildFlag) {
            addChild(previousOperation, node, right, errorCode);
            pop(stack, errorCode);
            addChildFlag = true;
        }
        if (getValue(node, errorCode) <= 47) {
            push(stack, node, errorCode);
        }
    }
    return tree;
}

void traversal(Tree tree, bool * errorCode) {
    Node * leaper = tree.root;
    while (getChild(leaper, left, errorCode) != NULL) {
        printf("%c", getValue(leaper, errorCode));
        leaper = getChild(leaper, left, errorCode);
    }
}