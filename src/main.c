#include <stdio.h>
#include <stdlib.h>
#include "../include/m2t.h"

int main()
{
    MoneySplit split = money_splt_in_two_halfs("45240,01");

    if (atoi(split.l_half) == 0 && atoi(split.r_half) == 0)
        printf("Nenhum valor foi fornecido\n");

    SplitInGroupsOfThree split_groups = split_in_groups_of_three(split.l_half);

    int result_count;
    ValueClassResult *results = identify_value_class(split_groups, &result_count);

    for (int i = 0; i < result_count; i++)
    {
        char *text = translate_value_to_txt(&results[i]);
        printf("%s", text);
        free(text);
    }

    printf("\n");
    free(results);

    return 0;
}