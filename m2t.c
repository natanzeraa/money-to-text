#include <stdio.h>
#include <string.h>

struct
{
    char l_half[50];
    char r_half[50];
} splt_money;

void splt_money_in_two_halfs(char *money)
{
    char *separator = strchr(money, ',');

    if (separator != NULL)
    {
        int position = separator - money;
        strncpy(splt_money.l_half, money, position);
        splt_money.l_half[position] = '\0';
        strcpy(splt_money.r_half, separator + 1);

        printf("Antes da virgula: %s\n", splt_money.l_half);
        printf("Depois da vírgula: %s\n", splt_money.r_half);
    }
    else
    {
        printf("Could not find ',' into money");
    }
}

int main()
{
    splt_money_in_two_halfs("123,45");
    return 0;
}