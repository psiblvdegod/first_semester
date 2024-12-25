#include "contactsSorting.h"
#include "mergeSort.h"
#include "stdio.h"
#include <stdlib.h>

#define INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION 1
#define MEMORY_ALLOCATION_ERROR 44
#define TESTS_FAILED_ERROR -1
#define NO_ERRORS 0
#define FILE_OPENING_ERROR 15

List *sortContacts(const char *filePath, SortingCriteria sortingCriteria, int *errorCode) {
    FILE *file = fopen(filePath, "r");
    if (file == NULL) {
        *errorCode = FILE_OPENING_ERROR;
        return NULL;
    }
    List *list = createList(errorCode);
    if (*errorCode != NO_ERRORS) {
        fclose(file);
        return NULL;
    }
    while (!feof(file)) {
        char *name = calloc(30, sizeof(char));
        char *number = calloc(30, sizeof(char));
        if (name == NULL || number == NULL) {
            *errorCode = MEMORY_ALLOCATION_ERROR;
            break;
        }
        fscanf(file, "%s%s", name, number);
        if (sortingCriteria == byName) {
            addToList(list, number, name, errorCode);
        }
        else {
            addToList(list, name, number, errorCode);
        }
        if (*errorCode != NO_ERRORS) {
            break;
        }
    }
    fclose(file);
    return mergeSort(list, errorCode);
}