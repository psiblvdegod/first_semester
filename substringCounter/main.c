#include <string.h>
#include <stdio.h>
#include <stdbool.h>

int substringCounter(const char *string, const char *substring, bool *errorCode) {
    if (string == NULL || substring == NULL || !substring[0]) {
        *errorCode = true;
        return -1;
    }
    int result = 0;
    const int substringLength = (int)strlen(substring);
    for (int i = 0; string[i] != '\0'; ++i) {
        bool isSubstring = true;
        for (int j = 0; j < substringLength; ++j) {
            if (string[i + j] != substring[j]) {
                isSubstring = false;
                break;
            }
        }
        if (isSubstring) {
            result += 1;
            i += substringLength;
        }
    }
    return result;
}

bool substringCounterTest() {
    const char * string = "4s44s444s4444s44444";
    const char * substring1 = "44";
    const char * substring2 = "s";
    const char * substring3 = "0";
    bool errorCode = false;
    bool test1 = substringCounter(string, substring1, &errorCode) == 6;
    bool test2 = substringCounter(string, substring2, &errorCode) == 4;
    bool test3 = substringCounter(string, substring3, &errorCode) == 0;
    return test1 && test2 && test3 && !errorCode;

}

int main(void) {
    if (!substringCounterTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    const char *string = "stringstringstring";
    const char *substring = "string";
    bool errorCode = false;
    const int result = substringCounter(string, substring, &errorCode);
    if (errorCode) {
        printf("Invalid value.\n");
        return -1;
    }
    printf("String: %s\nSubstring: %s\nResult: %d\n", string, substring, result);
}