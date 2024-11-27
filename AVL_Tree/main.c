#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

void queryProcessing(Node ** root, int userQuery, bool * errorCode) {
    if (userQuery == 1) {
        char * value = calloc(50, sizeof(char));
        char * key = calloc(50, sizeof (char));
        if (value == NULL || key == NULL) {
            printf("Memory allocation error.\n");
            return;
        }
        printf("Enter value and key.\n");
        int inputValidation = scanf("%s%s", value, key);
        while(getchar() != '\n');
        if (inputValidation != 2) {
            printf("Invalid value.\n");
            return;
        }
        bool isHeightChanged = false;
        Node *node = createNode(value, key, &isHeightChanged);
        if (*root == NULL) {
            *root = node;
        }
        else {
            insert(*root, node, &isHeightChanged);
        }
        if (!(*errorCode)) {
            printf("Node added.\n");
        }
        return;
    }
    if (userQuery == 2 || userQuery == 3) {
        char * key = calloc(50, sizeof (char));
        if (key == NULL) {
            printf("Memory allocation error.\n");
            return;
        }
        printf("Enter key.\n");
        int inputValidation = scanf("%s", key);
        while(getchar() != '\n');
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            return;
        }
        char * result = NULL;
        Node * node = getValueByKey(*root, key, &result);
        if (node != NULL && userQuery == 2) {
            printf("%s\n", getValue(node, errorCode));
        }
        else if (result != NULL && userQuery == 3) {
            printf("There is value with this key.\n");
        }
        else {
            printf("No such key.\n");
        }
        return;
    }
    if (userQuery == 4) {
        char * key = calloc(50, sizeof (char));
        if (key == NULL) {
            printf("Memory allocation error.\n");
            return;
        }
        printf("Enter key.\n");
        int inputValidation = scanf("%s", key);
        while(getchar() != '\n');
        if (inputValidation != 1) {
            printf("Invalid value.\n");
            return;
        }
        bool isHeightChanged = false;
        *root = deleteNode(*root, key, &isHeightChanged);
    }
}

int main(void) {
    treeTests();
    int userQuery = 1;
    bool errorCode = false;
    Node * root = NULL;
    while (userQuery) {
        printf("// 0 - quit // 1 - add // 2 - get // 3 - check // 4 - delete //\n");
        int inputValidation = scanf("%d", &userQuery);
        while(getchar() != '\n');
        if (inputValidation != 1  || userQuery < 0 || userQuery > 4) {
            printf("Invalid value.\n");
            continue;
        }
        queryProcessing(&root, userQuery, &errorCode);
        if (errorCode) {
            printf("Something went wrong.\n");
            errorCode = false;
        }
    }
}