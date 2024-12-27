#include "tests.h"
#include "tree.h"
#include "errorCode.h"
#include <stdio.h>
#include <stdlib.h>

/*
void queryProcessing(Tree ** tree, int userQuery, bool * errorCode) {
    if (userQuery == 1) {
        char * value = calloc(50, sizeof(char));
        if (value == NULL) {
            printf("Memory allocation error.\n");
            return;
        }
        int key = 0;
        printf("Enter value and key.\n");
        int inputValidation = scanf("%s%d", value, &key);
        while(getchar() != '\n');
        if (inputValidation != 2) {
            printf("Invalid value.\n");
            return;
        }
        Node *node = createNode(value, key, errorCode);
        if (getRoot(*tree) == NULL) {
            *tree = createTree(node, errorCode);
        }
        else {
            addNode(*tree, node, errorCode);
        }
        if (!(*errorCode)) {
            printf("Node added.\n");
        }
        return;
    }
    if (userQuery == 2 || userQuery == 3) {
        int key = 0;
        printf("Enter key.\n");
        int inputValidation = scanf("%d", &key);
        while(getchar() != '\n');
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            return;
        }
        Node * node = getNodeByKey(*tree, key, errorCode);
        if (node != NULL && userQuery == 2) {
            printf("%s\n", getValue(node, errorCode));
        }
        else if (node != NULL && userQuery == 3) {
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
        int inputValidation = scanf("%d", &key);
        while(getchar() != '\n');
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            return;
        }
        Node * node = getNodeByKey(*tree, key, errorCode);
        if (node != NULL) {
            disposeNode(*tree, node, errorCode);
            printf("Node deleted.\n");
        }
        else {
            printf("No such key.\n");
        }
    }
}
*/

int main(void) {
    int errorCode = NO_ERRORS;
    treeTests(&errorCode);
}