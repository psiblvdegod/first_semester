#include <stdio.h>
#include "list.h"
#include "mergeSort.h"
#include "tests.h"

int main(void) {
    if (!mergeTest() || !mergeSortTest()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    bool errorCode = false;
    printf("enter sorting criteria\nby number - 1\nby name - any other symbol\n");
    scanf("%d", &sortingCriteria);
    FILE * file = fopen("/Users/psiblvdegod/Desktop/123/homework/mergeSort/contacts.txt", "r");
    Node contacts = NULL;
    while(!feof(file)) {
        char * name = calloc(30, sizeof(char));
        char * number = calloc(30, sizeof(char));
        fscanf(file, "%s%s", name, number);
        Contact newContact = {sortingCriteria? number : name, sortingCriteria? name : number};
        contacts = addElement(contacts, newContact, &errorCode);
    }
    contacts = mergeSort(contacts, &errorCode);
    if (errorCode) {
        printf("Error.\n");
        return -1;
    }
    printAllContacts(contacts, &errorCode);
    fclose(file);
}