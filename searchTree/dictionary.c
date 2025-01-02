#include "dictionary.h"
#include "errorCode.h"
#include <stdlib.h>

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

Value searchInDictionary(Dictionary *dictionary, Key key, int *errorCode) {
    if (dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return nullptr;
    }
    return searchInTree(dictionary->root, key);
}

bool addToDictionary(Dictionary *dictionary, Value value, Key key, int *errorCode) {
    if (dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return false;
    }
    if (value == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return false;
    }
    dictionary->root = insertInTree(dictionary->root, value, key, errorCode);
    return *errorCode == NO_ERRORS;
}

bool deleteFromDictionary(Dictionary *dictionary, Key key, int *errorCode) {
    if (dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return false;
    }
    if (dictionary->root == nullptr) {
        return false;
    }
    bool wasDeletionSuccessful = false;
    dictionary->root = deleteFromTree(dictionary->root, key, &wasDeletionSuccessful, errorCode);
    return wasDeletionSuccessful && *errorCode == NO_ERRORS;
}

void deleteDictionary(Dictionary **dictionary, int *errorCode) {
    if (dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    if (*dictionary == nullptr) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    deleteTree(&(*dictionary)->root, errorCode);
    free(*dictionary);
    *dictionary = nullptr;
}