#pragma once
#include "list.h"

typedef enum {
    byName = 0,
    byNumber = 1
} SortingCriteria;

Node *sortContacts(const char *filePath, SortingCriteria sortingCriteria, int *errorCode);