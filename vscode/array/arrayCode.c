#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void arrayReversial(int *array, int left, int right)
{
    while (left < right)
    {
        int tmp = array[left];
        array[left] = array[right];
        array[right] = tmp;
        ++left;
        --right;
    }
}

bool arrayReversialTest()
{
    int array[] = {1, 2, 3, 4, 5};
    arrayReversial(array, 0, 4);
    for (int i = 1; i < 5; ++i)
    {
        if (array[i] > array[i - 1])
        {
            return false;
        }
    }
    return true;
}

int main(void)
{
    if (!arrayReversialTest())
    {
        printf("Error. Test failed.\n");
        return 0;
    }
    int m = 0, n = 0;
    printf("Enter n, m\n");
    scanf("%d%d", &n, &m);
    int *array = malloc((n + m) * sizeof(int));
    printf("Array\n");
    for (int i = 0; i < n + m; ++i)
    {
        array[i] = i;
        printf("%d ", array[i]);
    }
    arrayReversial(array, 0, n - 1);
    arrayReversial(array, n, n + m - 1);
    arrayReversial(array, 0, n + m - 1);
    printf("\nReversed array\n");
    for (int k = 0; k < n + m; ++k)
    {
        printf("%d ", array[k]);
    }
    free(array);
}