#include <stdio.h>
#include <string.h>

typedef struct
{
    char l_half[50];
    char r_half[50];
} MoneySplit;

MoneySplit money_splt_in_two_halfs(char *money)
{
    MoneySplit data;
    char *separator = strchr(money, ',');

    if (separator != NULL)
    {
        int position = separator - money;
        strncpy(data.l_half, money, position);
        data.l_half[position] = '\0';
        strcpy(data.r_half, separator + 1);
    }
    else
    {
        strcpy(data.l_half, money);
        strcpy(data.r_half, "00");
    }

    return data;
}

int main()
{
    MoneySplit split =  money_splt_in_two_halfs("543217,09");

    printf("Antes da virgula: %s\n", split.l_half);
    printf("Depois da vírgula: %s\n", split.r_half);
    return 0;
}

