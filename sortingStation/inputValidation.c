#include "inputValidation.h"
#include <stdlib.h>

bool parenthesesBalance(const char *string) {
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

bool inputValidation(const char *string) {
    const char *validCharacters = "0123456789()+-*/ ";
    for (int i = 0; string[i] != '\0'; ++i) {
        bool validStatus = false;
        for (int j = 0; validCharacters[j] != '\0'; ++j) {
            if (string[i] == validCharacters[j]) {
                validStatus = true;
            }
        }
        if (!validStatus) {
            return false;
        }
    }
    return parenthesesBalance(string);
}