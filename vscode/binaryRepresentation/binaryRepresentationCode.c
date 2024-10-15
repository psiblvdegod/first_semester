#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>
#define REGISTER_WIDTH 16

int *bin(int decimal)
{
    if (decimal < 0)
    {
        decimal = pow(2, REGISTER_WIDTH) + decimal;
    }
    int *binary = malloc(sizeof(int) * REGISTER_WIDTH);
    for (int i = 1; i <= REGISTER_WIDTH; ++i)
    {
        binary[REGISTER_WIDTH - i] = decimal % 2;
        decimal /= 2;
    }
    return binary;
}

int *binSum(int *binary1, int *binary2)
{
    for (int i = REGISTER_WIDTH - 1; i >= 0; --i)
    {
        binary1[i] += binary2[i];
        if (binary1[i] > 1)
        {
            binary1[i] -= 2;
            ++binary1[i - 1];
        }
    }
    return binary1;
}

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

int dec(int *binary)
{
    int result = 0;
    int sign = 1;
    if (binary[0])
    {
        sign = -1;
        for (int i = 0; i < REGISTER_WIDTH; ++i)
        {
            binary[i] = binary[i] ? 0 : 1;
        }
        binary = binSum(binary, bin(1));
    }
    for (int i = 0; i < REGISTER_WIDTH; ++i)
    {
        result += binary[REGISTER_WIDTH - i - 1] * pow(2, i);
    }
    return result * sign;
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
        return 0;
    }
    printf("Введите два числа в десятичной системе счисления.\n");
    int decimal1 = 0, decimal2 = 0;
    const int errorCode = scanf("%d%d", &decimal1, &decimal2);
    if (errorCode != 2)
    {
        printf("Ошибка. Недопустимое значение.\n");
        return 1;
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
    int *binary12 = binSum(binary1, binary2);
    printf("\nСумма в двоичной системе: ");
    for (int j = 0; j < REGISTER_WIDTH; ++j)
    {
        printf("%d", binary12[j]);
    }
    int decSum = dec(binary12);
    printf("\nСумма в десятичной системе = %d", decSum);
}