#include <stdio.h>
#include "tree.h"
#include "parse.h"
#include "tests.h"

int main(void) {
    if (!treeTests()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    bool errorCode = false;
    FILE * file = fopen("/Users/psiblvdegod/Desktop/homework/parseTree/text.txt", "r");
    if (file == NULL) {
        printf("Error. File not found.\n");
        return -1;
    }
    Tree * tree = buildTree(file, &errorCode);
    printf("Prefix tree notation:\n");
    printAllNodes(getRoot(tree), &errorCode);
    printf("\nCalculating result: %d ", calculateTree(getRoot(tree), &errorCode));
}
