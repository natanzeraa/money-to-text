#include <stdio.h>
#include <stdlib.h>
#include "../src/m2t.h"

int main()
{
    MoneySplit split = money_splt_in_two_halfs("1240,01");

    if (atoi(split.l_half) == 0 && atoi(split.r_half) == 0)
        printf("Nenhum valor foi fornecido\n");

    SplitInGroupsOfThree sigot = split_in_groups_of_three(split.l_half);
    identify_value_class(sigot);
    return 0;
}