#include "contactsSorting.h"
#include "errorCode.h"
#include "mergeSort.h"
#include "stdio.h"

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
        char name[30] = {'0'};
        char number[30] = {'0'};
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
    if (*errorCode != NO_ERRORS) {
        deleteList(&list, errorCode);
        return NULL;
    }
    return mergeSort(list, errorCode);
}