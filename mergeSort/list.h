#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include "contact.h"

typedef struct ListElement * Node;

typedef Contact Value;

Node addElement(Node node, Value value, bool * errorCode);

Node getNext(Node node, bool * errorCode);

Value getValue(Node node, bool * errorCode);

void disposeNode(Node node, bool * errorCode);