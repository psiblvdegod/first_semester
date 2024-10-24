#include "functions.h"

int main(void) {
    if (!commonestElementTest()) {
        printf("Error. Test failed.\n");
        return -1;
    }
    FILE * file = fopen("text.txt", "r");
    if (file == NULL) {
        printf("Error. File can not be opened.\n");
        return -1;
    }
    int errorCode = 0;
    Stack * stack = createStack();
    if (stack == NULL) {
        printf("Memory allocation error.\n");
        return -1;
    }
    int stackSize = 0;
    int elementFromFile = 0;
    while (!feof(file)) {
        if (!fscanf(file, "%d", &elementFromFile)) {
            printf("Invalid value in file.\n");
            return -1;
        }
        push(stack, elementFromFile, &errorCode);
        if (errorCode) {
            printf("Memory allocation error.\n");
            return -1;
        }
        ++stackSize;
    }
    const clock_t startTime = clock();
    int result = commonestElement(stack, stackSize, &errorCode);
    if (errorCode) {
        printf("Memory allocation error.\n");
        return -1;
    }
    const double duration = (double)(clock() - startTime) / CLOCKS_PER_SEC;
    printf("Commonest element = %d\n", result);
    printf("Duration: %lf", duration);
    fclose(file);
}
