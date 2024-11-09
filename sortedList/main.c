#include "list.h"
#include "tests.h"
#include <stdio.h>

int main(void) {
//    if (!listTests()){
//        printf("Error. Tests failed.\n");
//    }
    bool errorCode = false;
    List * list = createList(&errorCode);
    int userQuery = 1;
    int inputValidation = 1;
    while (userQuery) {
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
            Position currentPosition = getFirst(list, &errorCode);
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
            inputValidation = scanf("%d", &value);
            while (getchar() != '\n');
            Position currentPosition = getFirst(list, &errorCode);
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
            if (!listSize(list)) {
                printf("List is empty.\n");
                continue;
            }
            printf("Your list:\n");
            Position currentPosition = getFirst(list, &errorCode);
            for (int i = 0; i < listSize(list); ++i) {
                printf("%d ", getValue(currentPosition, &errorCode));
                currentPosition = getNext(currentPosition, &errorCode);
            }
            printf("\n");
        }
    }
}