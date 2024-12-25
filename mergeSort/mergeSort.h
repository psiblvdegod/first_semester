#pragma once
#include "list.h"

// merges two sorted lists to one and returns it
List *merge(List *firstList, List *secondList, int *errorCode);

// sorts list and returns it.
List *mergeSort(List *left, int *errorCode);