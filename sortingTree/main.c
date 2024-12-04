#include <stdio.h>
#include "sorting.h"
#include "tree.h"

int main(void) {
    bool errorCode = false;
    Value array[] = {"123", "234", "567","91" ,"12"};
    Node * tree = treeSorting(array, 5, &errorCode);
    int a = 0;
}
