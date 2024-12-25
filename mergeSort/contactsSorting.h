#pragma once
#include "list.h"

typedef enum {
    byName = 0,
    byNumber = 1
} SortingCriteria;

// opens file for read, reads contacts, creates list, fills it with contacts from file,
// sorts contacts list by name or by number depends on sortingCriteria, returns list
List *sortContacts(const char *filePath, SortingCriteria sortingCriteria, int *errorCode);