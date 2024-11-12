#include <stdio.h>
#include "list.h"
#include "mergeSort.h"
#include "tests.h"

enum {byName = 0, byNumber = 1} sortingCriteria;

int main(void) {
    mergeTest();
    bool errorCode = false;
    printf("enter sorting criteria 0/1 : name/number\n");
    scanf ("%d", &sortingCriteria);
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
    fclose(file);
}