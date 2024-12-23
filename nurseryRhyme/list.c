#include "list.h"

struct Node {
    Value value;
    struct Node *next;
    struct Node *previous;
};

Node *createNode(Value value, int *errorCode) {
    Node *node = calloc(1, sizeof(Node));
    if (node == NULL) {
        *errorCode = 44;
        free(node);
        return NULL;
    }
    node->value = value;
    return node;
}

Node *create(const int size, int *errorCode) {
    Node *head = createNode(0, errorCode);
    head->next = head;
    head->previous = head;
    head->value = 0;
    Node *current = head;
    for (int i = 1; i < size; ++i) {
        Node *new = createNode(i, errorCode);
        new->previous = current;
        new->next = current->next;
        current->next->previous = new;
        current->next = new;
        current = new;
    }
    return head;
}

Node *getNext(Node *node, int *errorCode) {
    return node->next;
}

Node *delete(Node *node, int *errorCode) {
    if (node == node->next) {
        free(node);
        return NULL;
    }
    node->next->previous = node->previous;
    node->previous->next = node->next;
    Node *next = node->next;
    free(node);
    return next;
}

Value getValue(Node *node, int *errorCode) {
    return node->value;
}