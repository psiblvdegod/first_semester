#include <stdio.h>
#include <stdbool.h>
#define STRING_MAX_LENGTH 1000

int substringCounter(char string[], char substring[], int *errorCode) {
    if (!string[0] || !substring[0]) {
        *errorCode = 1;
        return 0;
    }
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

bool substringCounterTest() {
    char string[]= "4s44s444s4444s44444";
    char substring1[] = "44";
    char substring2[] = "s";
    int errorCode = 0;
    return substringCounter(string, substring1, &errorCode) == 6 && substringCounter(string, substring2, &errorCode) == 4 ? true : false;
}

int main(void) {
    if (!substringCounterTest()) {
        printf("Error. Test failed.\n");
        return 0;
    }
    char s[STRING_MAX_LENGTH], s1[STRING_MAX_LENGTH];
    printf("Enter string and substring. No more %d symbols for each one.\n", STRING_MAX_LENGTH);
    scanf("%s%s", &s, &s1);
    int errorCode = 0;
    int result = substringCounter(s, s1, &errorCode);
    if (errorCode) {
        printf("Error. Invalid value.\n");
        return 0;
    }
    printf("\nresult: %d\n\n\n\n\n", result);
}
