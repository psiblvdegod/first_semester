#pragma once

#include "mergeSort.h"
#include "list.h"

// tests merge() from module mergeSort.c
void mergeTest(int *errorCode);

// tests mergeSort() from module mergeSort.c
void mergeSortTest(int *errorCode);

// tests sortContacts() from module contactsSorting.c
void contactsSortingTest(const char *filePath, int *errorCode);

// tests functions from module list.c
void listTests(int *errorCode);