#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>

bool palindrome(char string[], int *errorCode) {
    int stringLength = -1;
    int i = 0;
    while (string[i] != '\0') {
        ++i;
        ++stringLength;
    }
    if (stringLength < 1) {
        *errorCode = 1;
        return false;
    }
    int k = 0;
    int j = stringLength;
    while (k < j) {
        k = string[k] == ' ' ? k + 1 : k;
        j = string[j] == ' ' ? j - 1 : j;
        if (string[k] != string[j]) {
            return false;
        }
        --j;
        ++k;
    }
    return true;
}

bool test() {
    int errorCode = 0;
    char string1[] = "1234321";
    char string2[] = "a b c c b a";
    char string3[] = "12345321";
    return palindrome(string1, &errorCode) & palindrome(string2, &errorCode) & !palindrome(string3, &errorCode);
}

int main(void) {
    setlocale(LC_ALL, "Rus");
    if (!test()) {
        printf("Error. Test failed.\n");
        return 0;
    }
    int errorCode = 0;
    const char string[] = "я иду с мечем судия";
    bool result = palindrome(string, &errorCode);
    printf("result: %s\n", result ? "true" : "false");
}