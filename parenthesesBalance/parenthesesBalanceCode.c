#include <stdio.h>
#include <stdbool.h>

bool parenthesesBalance(char string[]) {
    int i = 0;
    int balanceStatus = 0;
    while (string[i] != '\0') {
        if (string[i] == '(') {
            ++balanceStatus;
        }
        if (string[i] == ')') {
            --balanceStatus;
        }
        if (balanceStatus < 0) {
            return false;
        }
        ++i;
    }
    if (balanceStatus != 0) {
        return false;
    }
    return true;
}

bool test() {
    bool test1 = parenthesesBalance("()()()");
    bool test2 = parenthesesBalance("())(()");
    bool test3 = parenthesesBalance("(((((");
    bool test4 = parenthesesBalance("((())");
    return test1 && !test2 && !test3 && !test4;
}

int main(void) {
    if (!test()) {
        printf("Test failed.\n");
        return 0;
    }
    char string[1000];
    printf("Enter string. No more 1000 symbols.\n");
    scanf("%s", &string);
    bool result = parenthesesBalance(string);
    printf("result: %s", result ? "true\n" : "false\n");
}
