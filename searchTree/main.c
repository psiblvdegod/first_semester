#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

void queryProcessing(Tree * tree, int userQuery, bool * errorCode) {
    if (userQuery == 1) {
        char *value = calloc(50, sizeof(char));
        int key = 0;
        printf("Enter value and key.\n");
        scanf("%s%d", value, &key);
        Node *node = createNode(value, key, errorCode);
        addNode(tree, node, errorCode);
        if (!errorCode) {
            printf("Node added.\n");
        } else {
            printf("Error.\n");
        }
        return;
    }
    if (userQuery == 2 || userQuery == 3) {
        int key = 0;
        printf("Enter key.\n");
        scanf("%d", &key);
        Node * node = getNodeByKey(getRoot(tree), key, errorCode);
        if (getKey(node, errorCode) == key && userQuery == 2) {
            printf("%s\n", getValue(node, errorCode));
        }
        else if (getKey(node, errorCode) == key && userQuery == 3) {
            printf("There is value with this key.\n");
        }
        else {
            printf("No such key.\n");
        }
        return;
    }
    if (userQuery == 4) {
        int key = 0;
        printf("Enter key.\n");
        scanf("%d", &key);
        Node * node = getNodeByKey(getRoot(tree), key, errorCode);
        if (getKey(node, errorCode) == key) {
            disposeNode(tree, node, errorCode);
            printf("Node deleted.\n");
        }
        else {
            printf("No such key.\n");
        }
    }
}

int main(void) {
    int userQuery = 1;
    bool errorCode = false;
    Node * root = createNode("root", 0, &errorCode);
    Tree * tree = createTree(root, &errorCode);
    while (userQuery) {
        printf("// 0 - quit // 1 - add // 2 - get // 3 - check // 4 - delete //\n");
        scanf("%d", &userQuery);
        queryProcessing(tree, userQuery, &errorCode);
    }

}