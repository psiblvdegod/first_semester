#include <stdio.h>
#include <stdbool.h>

bool parenthesesBalance(const char * string) {
    if (string == NULL) {
        return true;
    }
    int balanceStatus = 0;
    for (int i = 0; string[i] != '\0'; ++i) {
        if (balanceStatus < 0) {
            return false;
        }
        if (string[i] == '(') {
            ++balanceStatus;
        }
        if (string[i] == ')') {
            --balanceStatus;
        }
    }
    return balanceStatus == 0;
}

bool parenthesesBalanceTest() {
    const char * string1 = "()()()";
    const char * string2 = "())(()";
    const char * string3 = "string";
    const char * string4 = "";
    bool test1 = parenthesesBalance(string1);
    bool test2 = !parenthesesBalance(string2);
    bool test3 = parenthesesBalance(string3);
    bool test4 = parenthesesBalance(string4);
    return test1 && test2 && test3 && test4;

}

int main(void) {
    if (!parenthesesBalanceTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    const char * string = "(string)(string(string))string()";
    bool result = parenthesesBalance(string);
    printf("String: %s\nResult: %s\n", string, result ? "true" : "false");
}
