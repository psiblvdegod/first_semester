#include <stdio.h>
#include <stdbool.h>
#define STRING_MAX_LENGTH 1000
int substringCounter(char string[], char substring[]) {
    int result = 0;
    int stringIndex = 0, substringIndex = 0;
    int substringLength = 0, i = 0;
    while (substring[i] != '\0') {
        ++substringLength;
        ++i;
    }
    while (string[stringIndex] != '\0') {
        bool flag = true;
        while (substring[substringIndex] != '\0') {
            if (string[stringIndex + substringIndex] != substring[substringIndex]) {
                flag = false;
            }
            ++substringIndex;
        }
        substringIndex = 0;
        if (flag) {
            ++result;
            stringIndex += substringLength;
        }
        else {
            ++stringIndex;
        }
    }
    return result;
}
int main(void) {
    char s[STRING_MAX_LENGTH], s1[STRING_MAX_LENGTH];
    printf("Enter string and substring. No more %d symbols.\n", STRING_MAX_LENGTH);
    scanf("%s%s", &s, &s1);
    int a = substringCounter(s, s1);
    printf("%d", a);
}
