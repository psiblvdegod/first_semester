#include "list.h"

typedef struct ListElement {
    Value value;
    struct ListElement * previous;
    struct ListElement * next;
} ListElement;

Node addElement(Node node, Value value, bool * errorCode) {
    node = (ListElement *) node;
    ListElement * newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    newElement->previous = node;
    newElement->next = NULL;
    if (node != NULL) {
        if (node->next != NULL) {
            node->next->previous = newElement;
        }
        newElement->next = node->next;
        node->next = newElement;
    }
    return (Node) newElement;
}

Node deleteElement(Node node, bool * errorCode) {
    node = (ListElement *) node;
    if (node == NULL) {
        *errorCode = true;
        return NULL;
    }
    if (node->next != NULL) {
        node->next->previous = node->previous;
    }
    if (node->previous != NULL) {
        node->previous->next = node->next;
    }
    Node previousElement = (Node) node->previous;
    free(node);
    return previousElement;
}

Node getNext(Node node, bool * errorCode) {
    if (node == NULL) {
        return NULL;
    }
    return ((ListElement *) node)->next;
}

Node getPrevious(Node node, bool * errorCode) {
    if (node == NULL) {
        return NULL;
    }
    return ((ListElement *) node)->previous;
}


Value getValue(Node node, bool * errorCode) {
    if (node == NULL) {
        *errorCode = true;
    }
    else {
        return node->value;
    }
}
