#include "list.h"

typedef struct ListElement {
    Value value;
    struct ListElement * next;
} ListElement;

Node addElement(Node node, Value value, bool * errorCode) {
    node = (ListElement *) node;
    ListElement * newElement = calloc(1, sizeof(ListElement));
    newElement->value = value;
    newElement->next = node;
    return (Node) newElement;
}

Node getNext(Node node, bool * errorCode) {
    if (node == NULL) {
        return NULL;
    }
    return ((ListElement *) node)->next;
}

Value getValue(Node node, bool * errorCode) {
    if (node == NULL) {
        *errorCode = true;
    }
    else {
        return node->value;
    }
}

void disposeNode(Node node, bool * errorCode) {
    while (node != NULL) {
        Node temp = node;
        node = getNext(node, errorCode);
        free(temp);
    }
}