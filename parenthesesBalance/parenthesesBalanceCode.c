#include <stdio.h> 
#include <stdbool.h> 
#define STRING_MAX_SIZE 100 

bool parenthesesBalanceCheck(char *string) {
    int leftParenthesisCounter = 0, rightParenthesisCounter = 0;
    char lastParenthesis = '0';
    bool parenthesesBalance = true;
    for (int i = 0; i < STRING_MAX_SIZE; ++i) {
        if (string[i] == '(') {
            leftParenthesisCounter += 1;
            lastParenthesis = 'l';
        }
        if (string[i] == ')') {
            rightParenthesisCounter += 1;
            lastParenthesis = 'r';
            if (rightParenthesisCounter > leftParenthesisCounter) {
                parenthesesBalance = false;
                break;
            }
        }

    }
    if (lastParenthesis == 'l' || leftParenthesisCounter != rightParenthesisCounter) {
        parenthesesBalance = false;
    }
    return parenthesesBalance;
}

int main(void) {
    char inputString[STRING_MAX_SIZE] = "0";
    printf("Enter string. No more %d symbols.\n", STRING_MAX_SIZE);
    scanf("%s", &inputString);
    int result = parenthesesBalanceCheck(inputString);
    if (result == 1) {
        printf("result: true\n");
    }
    else {
        printf("result: false\n");
    }
}   