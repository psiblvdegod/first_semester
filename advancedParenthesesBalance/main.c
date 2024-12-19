#include "tests.h"

int main(void) {
    if (!parenthesesBalanceTest() || !stackTest()) {
        printf("Error. Tests failed.\n");
        return -1;
    }
    bool errorCode = false;
    const char *string = "{([{}])[()]}";
    bool result = parenthesesBalance(string, &errorCode);
    if (errorCode) {
        printf("Error.\n");
        return -1;
    }
    printf("string: %s\nresult: %s\n", string, result ? "true" : "false");
}
