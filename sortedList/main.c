#include "list.h"
#include "tests.h"
#include <stdio.h>

int main(void) {
    if (!listTests()){
        printf("Error. Tests failed.\n");
    }
    bool errorCode = false;
    List * list = createList(&errorCode);
    int userQuery = 1;
    while (userQuery) {
        if (errorCode) {
            printf("Error.\n");
            return -1;
        }
        printf("0 - quit // 1 - add // 2 - delete // 3 - print all\n");
        scanf("%d", &userQuery);
        if (userQuery == 1) {
            Value value = 0;
            printf("Enter value you want to add.\n");
            scanf("%d", &value);
            while (getchar() != '\n');
            if (listSize(list) == 0) {
                addElement(list, NULL, value, &errorCode);
                continue;
            }
            Position currentPosition = getGuardian(list, &errorCode);
            while (currentPosition != getLast(list, &errorCode)) {
                if (getValue(getNext(currentPosition, &errorCode), &errorCode) > value) {
                    addElement(list, currentPosition, value, &errorCode);
                    currentPosition = NULL;
                    break;
                }
                currentPosition = getNext(currentPosition, &errorCode);
            }
            if (currentPosition != NULL) {
                addElement(list, currentPosition, value, &errorCode);
            }
        }
        if (userQuery == 2) {
            if (!listSize(list)) {
                printf("List is empty.\n");
                continue;
            }
            Value value = 0;
            printf("Enter value you want to delete.\n");
            scanf("%d", &value);
            while (getchar() != '\n');
            Position currentPosition = getNext(getGuardian(list, &errorCode), &errorCode);
            Position lastPosition = getLast(list, &errorCode);
            while (true) {
                if (value == getValue(currentPosition, &errorCode)) {
                    deleteElement(list, currentPosition, &errorCode);
                    printf("Element deleted.\n");
                    break;
                }
                if (currentPosition == lastPosition) {
                    printf("There is no such element in the list.\n");
                    break;
                }
                currentPosition = getNext(currentPosition, &errorCode);
            }
        }
        if (userQuery == 3) {
            if (listSize(list) <= 1) {
                printf("List is empty.\n");
                continue;
            }
            printf("Your list:\n");
            Position currentPosition = getNext(getGuardian(list, &errorCode), &errorCode);
            for (int i = 0; i < listSize(list) - 1; ++i) {
                printf("%d ", getValue(currentPosition, &errorCode));
                currentPosition = getNext(currentPosition, &errorCode);
            }
            printf("\n");
        }
    }
    deleteList(&list, &errorCode);
}