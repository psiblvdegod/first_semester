#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "parse.h"

int main(void) {
    bool errorCode = false;
    FILE * file = fopen("/Users/psiblvdegod/Desktop/homework/parseTree/text.txt", "r");
    if (file == NULL) {
        printf("Error. File not found.\n");
        return -1;
    }
    Tree * tree = buildTree(file, &errorCode);
    printAllNodes(getRoot(tree), &errorCode);
}
