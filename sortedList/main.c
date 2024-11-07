#include "list.h"
#include "tests.h"
#include "queryProcessing.h"
#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

int main(void) {
    //SetConsoleOutputCP(1251);
    if (!listTests()){
        printf("Error. Tests failed.\n");
    }
    bool errorCode = false;
    List * list = createList(&errorCode);
    printf("1 - quit // 1 - add // 2 - delete // 3 - print all\n");
    int userQuery = 1;
    scanf("%d", &userQuery);
    bool isQuit = queryProcessing(userQuery, &list, &errorCode);
    if (isQuit);
    
}