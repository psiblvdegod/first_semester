#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

void queryProcessing(Tree * tree, int userQuery, bool * errorCode) {
    if (userQuery == 1) {
        char *value = calloc(50, sizeof(char));
        int key = 0;
        printf("enter value and key.\n");
        scanf("%s%d", value, &key);
        Node *node = createNode(value, key, errorCode);
        addNode(tree, node, errorCode);
        if (!errorCode) {
            printf("node added.\n");
        } else {
            printf("error.\n");
        }
        return;
    }
    if (userQuery == 2) {
        int key = 0;
        printf("enter key.\n");
        scanf("%d", &key);
        //Node * node = findNode();

        return;
    }
    if (userQuery == 3) {
        int key = 0;
        printf("enter key.\n");
        scanf("%d", &key);
        //Node * node = findNode();

        return;
    }
    if (userQuery == 4) {
        int key = 0;
        printf("enter key.\n");
        scanf("%d", &key);
        //Node * node = findNode();
    }
}