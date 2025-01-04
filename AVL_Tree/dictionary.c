#include "dictionary.h"
#include "errorCode.h"
#include <stdlib.h>
#include "tree.h"

struct Dictionary {
    Node *root;
};

Dictionary *createDictionary(int *errorCode) {
    Dictionary *dictionary = calloc(1, sizeof(Dictionary));
    if (dictionary == nullptr) {
        *errorCode = MEMORY_ALLOCATION_ERROR;
    }
    return dictionary;
}

void addToDictionary(Dictionary *dictionary, Value value, Value key, int *errorCode) {
    if (dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (value == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (key == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    Node *newNode = createNode(value, key, errorCode);
    if (*errorCode != NO_ERRORS) {
        return;
    }
    insertInTree(dictionary->root, newNode, errorCode);
}