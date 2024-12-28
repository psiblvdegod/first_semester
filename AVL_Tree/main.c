#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include "tests.h"

/*
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
            *root = insert(*root, node, &isHeightChanged);
        }
        if (!(*errorCode)) {
            printf("Node added.\n");
        }
    }
    else if (userQuery == 2 || userQuery == 3) {
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
        Value result = findValueByKey(*root, key);
        if (result == NULL) {
            printf("No such key.\n");
        }
        else if (userQuery == 2) {
            printf("%s\n", result);
        }
        else if (userQuery == 3) {
            printf("There is value with such key.\n");
        }
    }
    else if (userQuery == 4) {
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
        *root = dispose(*root, key, &isHeightChanged);
        if (!(*errorCode)) {
            printf("Node deleted.\n");
        }
    }
}
*/
int main(void) {
    return treeTests();
}