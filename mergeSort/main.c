#include <stdio.h>
#include "list.h"

enum {byName = 0, byNumber = 1} sortingCriteria;

int main(void) {
    bool errorCode = false;
    scanf ("%d", &sortingCriteria);
    FILE * file = fopen("/Users/psiblvdegod/Desktop/123/homework/mergeSort/contacts.txt", "r");
    List * contacts = createList(&errorCode);
    Position contactsPosition = NULL;
    char name[30], number[30];
    for (int i = 0; i < 5 ; ++i) {
        fscanf(file, "%s%s", name, number);
        Contact newContact = {sortingCriteria? number : name, sortingCriteria? name : number};
        addElement(contacts, &contactsPosition, newContact, &errorCode);
    }
    printf("%s%s", name, number);
    fclose(file);
}