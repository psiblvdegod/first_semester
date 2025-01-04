#include "typeDefinitions.h"
#include "AVL_Tree.h"
#include "errorCode.h"
#include "tests.h"
#include <stdio.h>
#include <string.h>

int AVLTreeTest() {
    int errorCode = NO_ERRORS;
    Node *root = nullptr;
    bool isHeightChanged = false;
    root = insertIntoAVLTree(root, createNode("111", "111", &errorCode), &isHeightChanged);
    if (errorCode != NO_ERRORS) {
        deleteAVLTree(root, &errorCode);
        return errorCode;
    }
    root = insertIntoAVLTree(root, createNode("222", "222", &errorCode), &isHeightChanged);
    if (errorCode != NO_ERRORS) {
        deleteAVLTree(root, &errorCode);
        return errorCode;
    }
    root = insertIntoAVLTree(root, createNode("333", "333", &errorCode), &isHeightChanged);
    if (errorCode != NO_ERRORS) {
        deleteAVLTree(root, &errorCode);
        return errorCode;
    }
    root = insertIntoAVLTree(root, createNode("444", "444", &errorCode), &isHeightChanged);
    if (errorCode != NO_ERRORS) {
        deleteAVLTree(root, &errorCode);
        return errorCode;
    }
    root = insertIntoAVLTree(root, createNode("555", "555", &errorCode), &isHeightChanged);
    if (errorCode != NO_ERRORS) {
        deleteAVLTree(root, &errorCode);
        return errorCode;
    }
    const bool searchTest1 = strcmp(searchInAVLTree(root, "111"), "111") == 0;
    const bool searchTest2 = searchInAVLTree(root, "") == nullptr;
    root = deleteFromAVLTree(root, "555", &isHeightChanged);
    root = deleteFromAVLTree(root, "333", &isHeightChanged);
    const bool searchTest3 = strcmp(searchInAVLTree(root, "444"), "444") == 0;
    const bool searchTest4 = searchInAVLTree(root, "333") == nullptr;
    deleteAVLTree(root, &errorCode);
    const bool test = searchTest1 && searchTest2 && searchTest3 && searchTest4;
    if (errorCode == NO_ERRORS && !test) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}

int invariantTest(const char *filePath) {
    int errorCode = NO_ERRORS;
    FILE *file = fopen(filePath, "r");
    if (file == nullptr) {
        return FILE_OPENING_ERROR;
    }
    Node *root = nullptr;
    while (!feof(file)) {
        char value[VALUE_MAX_SIZE] = {'0'};
        char key[VALUE_MAX_SIZE] = {'0'};
        fscanf(file, "%s%s", value, key);
        insertIntoTree(&root, value, key, &errorCode);
        if (errorCode != NO_ERRORS) {
            deleteTree(&root, &errorCode);
            fclose(file);
            return errorCode;
        }
    }
    fclose(file);
    const bool invariantTest = verifyAVLTreeInvariants(root, &errorCode);
    deleteTree(&root, &errorCode);
    if (errorCode == NO_ERRORS && !invariantTest) {
        return TESTS_FAILED_ERROR;
    }
    return errorCode;
}
