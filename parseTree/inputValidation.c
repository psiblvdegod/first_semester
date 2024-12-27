#include "inputValidation.h"
#include "errorCode.h"
#include <stdlib.h>

void inputValidation(const char *input, int *errorCode) {
    if (input == NULL) {
        *errorCode = INCORRECT_ARGUMENTS_PASSED_TO_FUNCTION;
        return;
    }
    int operatorsAmount = 0;
    int operandsAmount = 0;
    for (int i = 0; input[i] != '\0'; ++i) {
        if (input[i] == ' ') {
            continue;
        }
        else if ('0' <= input[i] && input[i] <= '9') {
            ++operandsAmount;
            while (input[i] != ' ' && input[i] != '\n' && input[i] != '\0') {
                ++i;
            }
        }
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' || input[i] == '/') {
            --operatorsAmount;
        }
        else {
            *errorCode = INCORRECT_EXPRESSION_IN_FILE;
            return;
        }
    }
    if (operatorsAmount != operandsAmount - 1) {
        *errorCode = INCORRECT_EXPRESSION_IN_FILE;
    }
}