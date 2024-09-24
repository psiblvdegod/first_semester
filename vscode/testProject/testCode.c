// print(input('string').count(input('substring'))) (T-T)

#include <stdio.h>
#include <stdbool.h>
int main(void) {
    char string[] = "101 201 301 401 501 601", substring[] = "01";
    int stringLength = sizeof(string) / sizeof(char) - 1;
    int substringLength = sizeof(substring) / sizeof(char) - 1;
    int result = 0;
    for (int i = 0; i < stringLength; ++i) {
        bool equalityChech = true;
        for (int j = 0; j < substringLength; ++j) {
            if (string[i + j] != substring[j]) {
                equalityChech = false;
            }
        }
        if (equalityChech == true) {
            result += 1;                            
            printf("%d", result);
        }
    }
}
                                                                                                                        