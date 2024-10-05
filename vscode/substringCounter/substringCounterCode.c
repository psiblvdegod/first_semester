#include <stdio.h>
#include <stdbool.h>
#define STRING_MAX_LENGTH 1000

int substringCounter(char string[], char substring[])
{
    int result = 0;
    int stringIndex = 0, substringIndex = 0;
    int substringLength = 0, i = 0;
    while (substring[i] != '\0')
    {
        ++substringLength;
        ++i;
    }
    while (string[stringIndex] != '\0')
    {
        bool flag = true;
        while (substring[substringIndex] != '\0')
        {
            if (string[stringIndex + substringIndex] != substring[substringIndex])
            {
                flag = false;
            }
            ++substringIndex;
        }
        substringIndex = 0;
        if (flag)
        {
            ++result;
            stringIndex += substringLength;
        }
        else
        {
            ++stringIndex;
        }
    }
    return result;
}

bool test()
{
    char string[] = "4s44s444s4444";
    char substring[] = "44";
    bool result = substringCounter(string, substring) == 4 ? true : false;
    return result;
}

int main(void)
{
    if (!test())
    {
        printf("Error. Test failed.\n");
        return 0;
    }
    char string[STRING_MAX_LENGTH], substring[STRING_MAX_LENGTH];
    printf("Enter string and substring. No more %d symbols.\n", STRING_MAX_LENGTH);
    scanf("%s%s", &string, &substring);
    int result = substringCounter(string, substring);
    printf("\nresult: %d", result);
}