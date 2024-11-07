#include "list.h"
#include "queryProcessing.h"
#include <stdio.h>

bool queryProcessing(int userQuery, List ** list, bool * errorCode) {
    switch (userQuery) {
        case 0:
            printf("Shutting down.\n");
            deleteList(&list);
            return true;
        case 1:
            printf("Enter value you want to add.\n");
            Value newValue = 0;
            scanf("%d", &newValue);
            Position newPosition = getFirst(*list, &errorCode);
            while (newValue < getValue(newPosition, &errorCode)) {
                newPosition = getNext(newPosition, &errorCode);
            }
            addElement(*list, newPosition, newValue, &errorCode);
            break;
            
        case 2: //СКОРЕЕ ВСЕГО НИХУЯ НЕ РАБОТАЕТ
            if (isEmpty(list)) {
                printf("List is empty. Nothing to delete\n");
            }
            else {
                Value deletingValue = 0;
                Position deletingPosition = getFirst(*list, &errorCode);
                while (deletingValue != getValue(deletingPosition, &errorCode)) {
                    deletingPosition = getNext(deletingPosition, &errorCode);
                    if (deletingPosition == NULL) {
                        printf("There is no such value in the list.\n");
                        break;
                    }
                }
            }
            break;
        case 3:
            if(getFirst(*list, &errorCode) == NULL) {
                printf("List is empty.\n");
                break;
            }
            else {
                printf("Your list:\n");
                Position currentPosition = getFirst(*list, &errorCode);
                Position lastPosition = getLast(*list, &errorCode);
                while (currentPosition != lastPosition) {
                    printf("%d ", getValue(currentPosition, &errorCode));
                }
                break;
            }
        default:
           printf("Invalid value.\n");
          break;  
    }
}