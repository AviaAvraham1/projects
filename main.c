#include <stdio.h>
#include <stdlib.h>

#include "RLEList.h"

/*
static int NumOfDigits(int num)
{
    if (num < 0)
        return -1;
    if (num == 0)
        return 1;

    int digits = 0;
    while (num != 0)
    {
        num /= 10;
        digits++;
    }
    return digits;
}

char getDigit(int num, int requiredDigit)
{
    //in 123 1 is the first digit
    int toLoop = NumOfDigits(num) - requiredDigit;
    for (int i = 0 ; i < toLoop; i++)
        num /= 10;
    return (char)((num % 10) + '0');
}

static char* intToString(int num, char **writeTo)
{
    char *c = *writeTo;
    int digits = NumOfDigits(num);
    for (int i = 0; i < digits; i++)
    {
        **writeTo = getDigit(num, i + 1);
        *writeTo += 1;
    }
    **writeTo = '\n';
    *writeTo = c;
    printf("converted is : %s",*writeTo);
    return 0;
}
*/
int main()
{
    RLEList  rle = RLEListCreate();
    RLEListAppend(rle,'A');
    RLEListAppend(rle,'A');
    char *a = malloc(20);
    char *c = RLEListExportToString(rle,a);
    printf(c);
    free(a);
    return 0;
}


