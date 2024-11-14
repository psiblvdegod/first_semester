#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
#include "parse.h"

int main(void) {
    bool errorCode = false;
    FILE * file = fopen("/Users/psiblvdegod/Desktop/123/homework/parseTree/text.txt", "r");
    if (file == NULL) {
        printf("Error. File not found.\n");
        return -1;
    }
    char * string = calloc(50, sizeof(char));
    fscanf(file, "%s", string);
    Tree * tree = buildTree(string, &errorCode);
    printf("123");
    free(string);
}
