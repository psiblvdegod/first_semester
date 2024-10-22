#include "functions.h"

bool binTest()
{
    int *bin1 = bin(65000), *bin2 = bin(535);
    int *bin3 = bin(10000), *bin4 = bin(-10000);
    int *binSum1 = binSum(bin1, bin2);
    int *binSum2 = binSum(bin3, bin4);
    for (int i = 0; i < REGISTER_WIDTH; ++i)
    {
        if (binSum1[i] != 1 || binSum2[i] != 0)
        {
            return false;
        }
    }
    return true;
}

bool decTest()
{
    int *binary1 = bin(5);
    int *binary2 = bin(-5);
    return (dec(binary1) == 5 && dec(binary2) == -5);
}

int main(void)
{
    setlocale(LC_ALL, "Rus");
    if (!decTest() || !binTest())
    {
        printf("Ошибка. Тесты провалены.\n");
        return -1;
    }
    printf("Введите два числа в десятичной системе счисления.\n");
    int decimal1 = 0, decimal2 = 0;
    const int inputValidation = scanf("%d%d", &decimal1, &decimal2);
    if (inputValidation != 2)
    {
        printf("Ошибка. Недопустимое значение.\n");
        return -1;
    }
    int *binary1 = bin(decimal1);
    int *binary2 = bin(decimal2);
    printf("Первое число: ");
    for (int i = 0; i < REGISTER_WIDTH; ++i)
    {
        printf("%d", binary1[i]);
    }
    printf("\nВторое число: ");
    for (int k = 0; k < REGISTER_WIDTH; ++k)
    {
        printf("%d", binary2[k]);
    }
    int *binarySum = binSum(binary1, binary2);
    printf("\nСумма в двоичной системе: ");
    for (int j = 0; j < REGISTER_WIDTH; ++j)
    {
        printf("%d", binarySum[j]);
    }
    int decimalSum = dec(binarySum);
    printf("\nСумма в десятичной системе = %d", decimalSum);
}
