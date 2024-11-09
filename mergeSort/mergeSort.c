#include "mergeSort.h"
/*
List * merge(List * firstList, List * secondList, bool * errorCode) {
    List * mergedList = createList(errorCode);
    Position positionMergedList = NULL;
    Position positionFirst = getFirst(firstList, errorCode);
    Position positionSecond = getFirst(secondList, errorCode);

    while (positionFirst != NULL || positionSecond != NULL) {
        Value valueFromFirst = getValue(positionFirst, errorCode);
        Value valueFromSecond = getValue(positionSecond, errorCode);
        if (positionFirst == NULL) {
            while (positionSecond != NULL) {
                addElement(mergedList, &positionSecond, )
            }
        }
        if (valueFromFirst < valueFromSecond) {
            addElement(mergedList, &positionMergedList, valueFromFirst, errorCode);
            if (positionFirst != getLast(firstList, errorCode)) {
                positionFirst = getNext(positionFirst, errorCode);
            }
        }
        else {
            addElement(mergedList, &positionMergedList, valueFromSecond, errorCode);
            if (positionSecond != getLast(secondList, errorCode)) {
                positionSecond = getNext(positionSecond, errorCode);
            }
        }

    }
    //deleteList(&firstList, errorCode);
    //deleteList(&secondList, errorCode);
    return mergedList;
}*/