#include "typeDefinitions.h"
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

void addToDictionary(Dictionary *dictionary, Value value, Key key, int *errorCode) {
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
    insertIntoTree(&dictionary->root, value, key, errorCode);
}

Value searchInDictionary(Dictionary *dictionary, Key key, int *errorCode) {
    if (dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    if (key == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    return searchInTree(dictionary->root, key);
}

void deleteFromDictionary(Dictionary *dictionary, Key key, int *errorCode) {
    if (dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (key == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    deleteFromTree(&dictionary->root, key, errorCode);
}

void deleteDictionary(Dictionary **dictionary, int *errorCode) {
    if (dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (*dictionary == nullptr) {
        return;
    }
    if ((*dictionary)->root == nullptr) {
        free(*dictionary);
        return;
    }
    deleteTree(&(*dictionary)->root, errorCode);
    free(*dictionary);
    *dictionary = nullptr;
}

