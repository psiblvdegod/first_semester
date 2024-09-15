#include <stdio.h> 
int swap(int *left, int *right) {
    *left = *left + *right;
    *right = *left - *right;
    *left = *left - *right;
}

int main(void) {
    int integer1 = 0, integer2 = 0;
    printf("Enter 2 integer. Use space or enter to separate.\n");
    scanf("%d%d", &integer1, &integer2);
    swap(&integer1, &integer2);
    printf("integer1 = %d, integer2 = %d\n", integer1, integer2);
}